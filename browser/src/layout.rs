#![allow(unused_parens)]
#![allow(unused_variables)]
#![allow(non_snake_case)]
#![allow(dead_code)]

use crate::style::{StyledNode, Style, Display, Edge, Pixels};
use crate::paint::{DisplayList, DisplayCommand};
use std::default::Default;
use itertools::Itertools;

#[derive(Clone, Copy, Default, PartialEq, Debug)]
pub struct Rect {
    x: Pixels,
    y: Pixels,
    width: Pixels,
    height: Pixels
}

impl Rect {
    pub fn expanded_by(&self, edge: Edge<Pixels>) -> Rect {
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
    pub fn empty() -> FloatList {
        return FloatList(Vec::new());
    }
    pub fn addLeft(&self, adjusted: Pixels, available: Pixels, width: Pixels, height: Pixels, clearance: bool) -> FloatList {
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
    pub fn new(box_type: BoxType, style: &'a Style) -> Self {
        return LayoutBox {
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

pub fn layout_tree<'a>(node: &'a StyledNode<'a>, width: usize, height: usize) -> LayoutBox<'a> {
    let mut root_box = build_layout_tree(node);
    root_box.container.width = width as Pixels;
    root_box.layout();
    return root_box;
}

pub fn build_layout_tree<'a>(style_node: &'a StyledNode<'a>) -> LayoutBox<'a> {
    let box_type = match style_node.specified.display {
        Display::Inline => BoxType::Inline,
        Display::Block => BoxType::Block,
        Display::Float => BoxType::Float,
        Display::None => BoxType::None
    };
    let style = &style_node.specified;
    let mut root = LayoutBox::new(box_type, style);
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
    pub fn render(&self, list: &mut DisplayList) -> () {
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

impl<'a> LayoutBox<'a> {
    pub fn layout(&mut self) -> () {
        match self.class {
            BoxType::None => { },
            BoxType::Block => {
                self.padding.bottom = self.style.padding.bottom;
                self.margin.bottom = self.style.margin.bottom.value();
                self.border.bottom = self.style.border.bottom;
                self.underflow = (self.container.width - ((((((self.style.margin.left.value() + self.style.margin.right.value()) + self.style.border.left) + self.style.border.right) + self.style.padding.left) + self.style.padding.right) + self.style.width.value()));
                self.padding.top = self.style.padding.top;
                self.content_box.width = if self.style.width.is_auto() { self.underflow.max(0.0) } else { self.style.width.value() };
                self.border.left = self.style.border.left;
                self.margin.left = if self.style.margin.left.is_auto() { if (self.style.width.is_auto() || (self.underflow < 0.0)) { 0.0 } else { if self.style.margin.right.is_auto() { (self.underflow / 2.0) } else { self.underflow } } } else { self.style.margin.left.value() };
                self.margin_acc.bottom.collapse = (((self.padding.bottom == 0.0) && (self.border.bottom == 0.0)) && self.style.height.is_auto());
                self.floatLstOut = self.floatLstIn.clone();
                self.padding.left = self.style.padding.left;
                self.padding.right = self.style.padding.right;
                self.margin.top = self.style.margin.top.value();
                self.border.top = self.style.border.top;
                self.content_box.y = ((((self.container.y + self.container.height) + self.margin.top) + self.border.top) + self.padding.top);
                self.content_box.x = (((self.container.x + self.margin.left) + self.border.left) + self.padding.left);
                self.content_box.height = 0.0;
                for children_i in self.children.iter_mut() {
                    children_i.container.x = self.content_box.x;
                    children_i.container.y = self.content_box.y;
                    children_i.container.width = self.content_box.width;
                    children_i.container.height = self.content_box.height;
                    children_i.floatLstIn = FloatList::empty();
                    children_i.layout();
                    self.content_box.height = (self.content_box.height + children_i.computedHeight);
                }
                self.padding_box.x = (self.content_box.x - self.padding.left);
                self.padding_box.y = (self.content_box.y - self.padding.top);
                self.padding_box.width = ((self.content_box.width + self.padding.left) + self.padding.right);
                self.content_box.height = if self.style.height.is_auto() { self.content_box.height } else { self.style.height.value() };
                self.margin_acc.top.collapse = ((self.padding.top == 0.0) && (self.border.top == 0.0));
                self.border_box.y = (self.padding_box.y - self.border.top);
                self.margin_box.y = (self.border_box.y - self.margin.top);
                self.padding_box.height = ((self.content_box.height + self.padding.top) + self.padding.bottom);
                self.border_box.height = ((self.padding_box.height + self.border.top) + self.border.bottom);
                self.margin_box.height = ((self.border_box.height + self.margin.top) + self.margin.bottom);
                self.computedHeight = self.margin_box.height;
                self.border_box.x = (self.padding_box.x - self.border.left);
                self.margin_box.x = (self.border_box.x - self.margin.left);
                self.margin.right = if (self.style.width.is_auto() && (self.underflow < 0.0)) { (self.style.margin.right.value() + self.underflow) } else { if self.style.margin.right.is_auto() { if self.style.width.is_auto() { 0.0 } else { if self.style.margin.left.is_auto() { (self.underflow / 2.0) } else { self.underflow } } } else { if ((!self.style.margin.left.is_auto()) || (!self.style.width.is_auto())) { (self.style.margin.right.value() + self.underflow) } else { self.style.margin.right.value() } } };
                self.border.right = self.style.border.right;
                self.border_box.width = ((self.padding_box.width + self.border.left) + self.border.right);
                self.margin_box.width = ((self.border_box.width + self.margin.left) + self.margin.right);
            },
            BoxType::Inline => {
                self.border.bottom = self.style.border.bottom;
                self.padding.top = self.style.padding.top;
                self.padding.bottom = self.style.padding.bottom;
                self.content_box.height = 0.0;
                self.content_box.height = self.style.height.value();
                self.padding_box.height = ((self.content_box.height + self.padding.top) + self.padding.bottom);
                self.margin.bottom = self.style.margin.bottom.value();
                self.border.top = self.style.border.top;
                self.border_box.height = ((self.padding_box.height + self.border.top) + self.border.bottom);
                self.margin.top = self.style.margin.top.value();
                self.margin_box.height = ((self.border_box.height + self.margin.top) + self.margin.bottom);
                self.padding.left = self.style.padding.left;
                self.border.left = self.style.border.left;
                self.margin_acc.bottom.collapse = (((self.padding.bottom == 0.0) && (self.border.bottom == 0.0)) && self.style.height.is_auto());
                self.content_box.y = ((((self.container.y + self.container.height) + self.margin.top) + self.border.top) + self.padding.top);
                self.padding_box.y = (self.content_box.y - self.padding.top);
                self.border_box.y = (self.padding_box.y - self.border.top);
                self.margin_box.y = (self.border_box.y - self.margin.top);
                self.floatLstOut = self.floatLstIn.clone();
                self.computedHeight = self.content_box.height;
                self.padding.right = self.style.padding.right;
                self.border.right = self.style.border.right;
                self.underflow = (self.container.width - ((((((self.style.margin.left.value() + self.style.margin.right.value()) + self.style.border.left) + self.style.border.right) + self.style.padding.left) + self.style.padding.right) + self.style.width.value()));
                self.content_box.width = if self.style.width.is_auto() { self.underflow.max(0.0) } else { self.style.width.value() };
                self.padding_box.width = ((self.content_box.width + self.padding.left) + self.padding.right);
                self.border_box.width = ((self.padding_box.width + self.border.left) + self.border.right);
                self.margin.right = if (self.style.width.is_auto() && (self.underflow < 0.0)) { (self.style.margin.right.value() + self.underflow) } else { if self.style.margin.right.is_auto() { if self.style.width.is_auto() { 0.0 } else { if self.style.margin.left.is_auto() { (self.underflow / 2.0) } else { self.underflow } } } else { if ((!self.style.margin.left.is_auto()) || (!self.style.width.is_auto())) { (self.style.margin.right.value() + self.underflow) } else { self.style.margin.right.value() } } };
                self.margin_acc.top.collapse = ((self.padding.top == 0.0) && (self.border.top == 0.0));
                self.margin.left = if self.style.margin.left.is_auto() { if (self.style.width.is_auto() || (self.underflow < 0.0)) { 0.0 } else { if self.style.margin.right.is_auto() { (self.underflow / 2.0) } else { self.underflow } } } else { self.style.margin.left.value() };
                self.content_box.x = (((self.container.x + self.margin.left) + self.border.left) + self.padding.left);
                self.margin_box.width = ((self.border_box.width + self.margin.left) + self.margin.right);
                self.padding_box.x = (self.content_box.x - self.padding.left);
                self.border_box.x = (self.padding_box.x - self.border.left);
                self.margin_box.x = (self.border_box.x - self.margin.left);
            },
            BoxType::Float => {
                self.underflow = (self.container.width - ((((((self.style.margin.left.value() + self.style.margin.right.value()) + self.style.border.left) + self.style.border.right) + self.style.padding.left) + self.style.padding.right) + self.style.width.value()));
                self.margin.right = 0.0;
                self.margin.left = 0.0;
                self.computedHeight = 0.0;
                self.padding.right = 0.0;
                self.padding.bottom = 0.0;
                self.content_box.width = if self.style.width.is_auto() { self.underflow.max(0.0) } else { self.style.width.value() };
                self.border.right = self.style.border.right;
                self.border.bottom = self.style.border.bottom;
                self.margin.top = 0.0;
                self.padding.left = 0.0;
                self.border.left = self.style.border.left;
                self.border.top = self.style.border.top;
                self.padding_box.width = ((self.content_box.width + self.padding.left) + self.padding.right);
                self.padding.top = 0.0;
                self.border_box.width = ((self.padding_box.width + self.border.left) + self.border.right);
                self.margin_box.width = ((self.border_box.width + self.margin.left) + self.margin.right);
                self.content_box.y = ((((self.container.y + self.container.height) + self.margin.top) + self.border.top) + self.padding.top);
                self.content_box.x = (((self.container.x + self.margin.left) + self.border.left) + self.padding.left);
                self.padding_box.y = (self.content_box.y - self.padding.top);
                self.content_box.height = 0.0;
                for children_i in self.children.iter_mut() {
                    children_i.container.x = self.content_box.x;
                    children_i.container.width = self.content_box.width;
                    children_i.container.y = self.content_box.y;
                    children_i.container.height = self.content_box.height;
                    children_i.floatLstIn = FloatList::empty();
                    children_i.layout();
                    self.content_box.height = (self.content_box.height + children_i.margin_box.height);
                }
                self.content_box.height = if self.style.height.is_auto() { self.content_box.height } else { self.style.height.value() };
                self.margin_acc.top.collapse = ((self.padding.top == 0.0) && (self.border.top == 0.0));
                self.padding_box.x = (self.content_box.x - self.padding.left);
                self.border_box.x = (self.padding_box.x - self.border.left);
                self.border_box.y = (self.padding_box.y - self.border.top);
                self.margin_box.y = (self.border_box.y - self.margin.top);
                self.margin.bottom = 0.0;
                self.margin_acc.bottom.collapse = (((self.padding.bottom == 0.0) && (self.border.bottom == 0.0)) && self.style.height.is_auto());
                self.padding_box.height = ((self.content_box.height + self.padding.top) + self.padding.bottom);
                self.border_box.height = ((self.padding_box.height + self.border.top) + self.border.bottom);
                self.margin_box.height = ((self.border_box.height + self.margin.top) + self.margin.bottom);
                self.floatLstOut = self.floatLstIn.addLeft(0.0, self.container.width, self.style.width.value(), self.margin_box.height, false);
                self.margin_box.x = (self.border_box.x - self.margin.left);
            }
        }
    }
}
