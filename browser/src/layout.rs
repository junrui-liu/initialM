#![allow(unused_parens)]
#![allow(unused_variables)]
#![allow(non_snake_case)]
#![allow(dead_code)]

use crate::dom;
use crate::style::{StyledNode, Style, Display, Edge, Pixels};
use crate::paint::{DisplayList, DisplayCommand};
use std::default::Default;
use std::fmt;
use itertools::Itertools;

#[derive(Clone, Copy, Default, PartialEq, Debug)]
pub struct Rect {
    x: Pixels,
    y: Pixels,
    width: Pixels,
    height: Pixels
}

impl Rect {
    fn expanded_by(&self, edge: Edge<Pixels>) -> Rect {
        return Rect {
            x: (self.x - edge.left),
            y: (self.y - edge.top),
            width: (self.width + (edge.left + edge.right)),
            height: (self.height + (edge.top + edge.bottom))
        };
    }
}

#[derive(Clone, Copy, Default, PartialEq, Debug)]
pub struct CollapsibleMargin {
    positive: Pixels,
    negative: Pixels,
    collapse: bool
}

#[derive(Clone, Copy, Default, PartialEq, Debug)]
pub struct MarginAccumulator {
    clearance: bool,
    weirdness: bool,
    top: CollapsibleMargin,
    bottom: CollapsibleMargin
}

#[derive(Clone, Copy, Default, PartialEq, Debug)]
pub struct FloatItem {
    adjusted: Pixels,
    available: Pixels,
    width: Pixels,
    height: Pixels,
    clearance: bool
}

#[derive(Clone)]
pub struct FloatList(Vec<FloatItem>);

impl FloatList {
    fn empty() -> FloatList {
        return FloatList(Vec::new());
    }
    fn addLeft(&self, adjusted: Pixels, available: Pixels, width: Pixels, height: Pixels, clearance: bool) -> FloatList {
        let mut list = self.clone();
        let item = FloatItem {
            adjusted: adjusted,
            available: available,
            width: width,
            height: height,
            clearance: clearance
        };
        list.0.push(item);
        return list;
    }
}

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
pub enum BoxType {
    None,
    Inline,
    Block,
    Float
}

pub struct LayoutBox<'a> {
    element: Option<dom::NodeId>,
    container: Rect,
    content_box: Rect,
    padding_box: Rect,
    border_box: Rect,
    margin_box: Rect,
    computedHeight: Pixels,
    margin_acc: MarginAccumulator,
    padding: Edge<Pixels>,
    border: Edge<Pixels>,
    margin: Edge<Pixels>,
    floatLstIn: FloatList,
    floatLstOut: FloatList,
    underflow: Pixels,
    style: &'a Style,
    anonymous: bool,
    class: BoxType,
    children: Vec<LayoutBox<'a>>
}

impl<'a> LayoutBox<'a> {
    fn new(box_type: BoxType, style: &'a Style) -> Self {
        return LayoutBox {
            element: None,
            container: Rect::default(),
            content_box: Rect::default(),
            padding_box: Rect::default(),
            border_box: Rect::default(),
            margin_box: Rect::default(),
            computedHeight: 0.0,
            margin_acc: MarginAccumulator::default(),
            floatLstIn: FloatList::empty(),
            floatLstOut: FloatList::empty(),
            padding: Edge::default(),
            border: Edge::default(),
            margin: Edge::default(),
            underflow: 0.0,
            style: style,
            anonymous: true,
            class: box_type,
            children: Vec::new()
        };
    }
}

impl<'a> fmt::Display for LayoutBox<'a> {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        if (self.class == BoxType::None) {
            write!(f, "#|")?;
        }
        write!(f, "(")?;
        match self.element {
            None => {
                write!(f, "[ANON]")?;
            },
            Some(id) => {
                let kind = match self.class {
                    BoxType::None => "NONE",
                    BoxType::Block => "BLOCK",
                    BoxType::Float => "BLOCK",
                    BoxType::Inline => "INLINE"
                };
                let x = self.content_box.x;
                let y = self.content_box.y;
                let w = self.content_box.width;
                let h = self.content_box.height;
                write!(f, "[{} :x {} :y {} :w {} :h {} :elt {}]", kind, x, y, w, h, id)?;
            }
        }
        for child in self.children.iter() {
            write!(f, " {}", child)?;
        }
        write!(f, ")")?;
        if (self.class == BoxType::None) {
            write!(f, "|#")?;
        }
        return Result::Ok(());
    }
}

pub fn layout_tree<'a>(node: &'a StyledNode<'a>, width: usize, height: usize) -> LayoutBox<'a> {
    let mut root_box = build_layout_tree(node);
    root_box.container.width = width as Pixels;
    root_box.layout();
    println!("(define-layout (doc-2 :matched true :w {} :h {} :fs 16 :scrollw 0) ([VIEW :w {}] {}))", width, height, width, root_box);
    return root_box;
}

fn build_layout_tree<'a>(style_node: &'a StyledNode<'a>) -> LayoutBox<'a> {
    let box_type = match style_node.specified.display {
        Display::Inline => BoxType::Inline,
        Display::Block => BoxType::Block,
        Display::Float => BoxType::Float,
        Display::None => BoxType::None
    };
    let style = &style_node.specified;
    let mut root = LayoutBox::new(box_type, style);
    root.element = Some(style_node.node.number);
    root.anonymous = false;
    let children = style_node.children.iter().map(build_layout_tree);
    for (box_type, children) in &children.group_by(|child| child.class) {
        if (root.class != box_type) {
            let mut wrapper = LayoutBox::new(root.class, style);
            wrapper.children.extend(children);
            root.children.push(wrapper);
        } else {
            root.children.extend(children);
        }
    }
    return root;
}

pub fn display_list<'a>(layout_root: &LayoutBox<'a>) -> DisplayList {
    let mut list = Vec::new();
    layout_root.render(&mut list);
    return list;
}

impl<'a> LayoutBox<'a> {
    fn render(&self, list: &mut DisplayList) -> () {
        list.push(DisplayCommand::SolidColor {
            color: self.style.background_color,
            x: self.border_box.x,
            y: self.border_box.y,
            width: self.border_box.width,
            height: self.border_box.height
        });
        list.push(DisplayCommand::SolidColor {
            color: self.style.border_color,
            x: self.border_box.x,
            y: self.border_box.y,
            width: self.border.left,
            height: self.border_box.height
        });
        list.push(DisplayCommand::SolidColor {
            color: self.style.border_color,
            x: ((self.border_box.x + self.border_box.width) - self.border.right),
            y: self.border_box.y,
            width: self.border.right,
            height: self.border_box.height
        });
        list.push(DisplayCommand::SolidColor {
            color: self.style.border_color,
            x: self.border_box.x,
            y: self.border_box.y,
            width: self.border_box.width,
            height: self.border.top
        });
        list.push(DisplayCommand::SolidColor {
            color: self.style.border_color,
            x: self.border_box.x,
            y: ((self.border_box.y + self.border_box.height) - self.border.bottom),
            width: self.border_box.width,
            height: self.border.bottom
        });
        for child in self.children.iter().rev() {
            child.render(list);
        }
    }
}

