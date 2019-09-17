/*
 * Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     rekols <rekols@foxmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <DPalette>

#include "basickeypad.h"
#include "dthememanager.h"

const BasicKeypad::KeyDescription BasicKeypad::keyDescriptions[] = {
    { "C", Key_Clear, 1, 0 },
    { "%", Key_Percent, 1, 1 },
    { "", Key_Backspace, 1, 2 },
    { "", Key_Div, 1, 3 },

    { "7", Key_7, 2, 0 },
    { "8", Key_8, 2, 1 },
    { "9", Key_9, 2, 2 },
    { "", Key_Mult, 2, 3 },

    { "4", Key_4, 3, 0 },
    { "5", Key_5, 3, 1 },
    { "6", Key_6, 3, 2 },
    { "", Key_Min, 3, 3 },

    { "1", Key_1, 4, 0 },
    { "2", Key_2, 4, 1 },
    { "3", Key_3, 4, 2 },
    { "", Key_Plus, 4, 3 },

    { "0", Key_0, 5, 0 },
    { ".", Key_Point, 5, 1 },
    { "( )", Key_Brackets, 5, 2 },
    { "=", Key_Equals, 5, 3 }
};

static DPushButton* createSpecialKeyButton(BasicKeypad::Buttons key) {
    IconButton *button = new IconButton(16, 16);

    if (key == BasicKeypad::Key_Div) {
        button->setIcon(":/images/div_normal.svg");
    } else if (key == BasicKeypad::Key_Mult) {
        button->setIcon(":/images/mult_normal.svg");
    } else if (key == BasicKeypad::Key_Min) {
        button->setIcon(":/images/min_normal.svg");
    } else if (key == BasicKeypad::Key_Plus) {
        button->setIcon(":/images/plus_normal.svg");
    } else if (key == BasicKeypad::Key_Backspace) {
        button->setIconStateSizes(23, 26);
        button->setIcon(QString(":/images/delete_light_normal.svg"));
    }

    /*    if (key == BasicKeypad::Key_Div) {
            button->setFixedSize(10, 13);
            button->setNormalPic(":/images/÷_normal.svg");
            button->setHoverPic(":/images/÷_press.svg");
            button->setPressPic(":/images/÷_hover.svg");
        } else if (key == BasicKeypad::Key_Mult) {
            button->setFixedSize(10, 13);
            button->setNormalPic(":/images/÷_normal.svg");
            button->setHoverPic(":/images/÷_press.svg");
            button->setPressPic(":/images/÷_hover.svg");
        } else if (key == BasicKeypad::Key_Min) {
            button->setFixedSize(10, 13);
            button->setNormalPic(":/images/÷_normal.svg");
            button->setHoverPic(":/images/÷_press.svg");
            button->setPressPic(":/images/÷_hover.svg");
        } else if (key == BasicKeypad::Key_Plus) {
            button->setFixedSize(10, 13);
            button->setNormalPic(":/images/÷_normal.svg");
            button->setHoverPic(":/images/÷_press.svg");
            button->setPressPic(":/images/÷_hover.svg");
        } else if (key == BasicKeypad::Key_Backspace) {
            button->setFixedSize(23, 26);
            button->setNormalPic(":/images/delete_light_normal.svg");
            button->setHoverPic(":/images/delete_light_hover.svg");
            button->setPressPic(":/images/delete_light_press.svg");
        }*/

    return button;
}

BasicKeypad::BasicKeypad(QWidget *parent)
    : QWidget(parent),
      m_layout(new QGridLayout(this)),
      m_mapper(new QSignalMapper(this))
{
    m_layout->setMargin(0);
    m_layout->setSpacing(5);
    m_layout->setContentsMargins(0,0,0,0);

    initButtons();
    initUI();

    connect(m_mapper, SIGNAL(mapped(int)), SIGNAL(buttonPressed(int)));
    //connect(DThemeManager::instance(), &DThemeManager::themeChanged, this, &BasicKeypad::handleThemeChanged);
}

BasicKeypad::~BasicKeypad()
{
}

DPushButton* BasicKeypad::button(Buttons key)
{
    return m_keys.value(key).first;
}

void BasicKeypad::animate(Buttons key)
{
    TextButton *btn = static_cast<TextButton *>(button(key));
    btn->animate();
}

void BasicKeypad::initButtons()
{
    const int count = sizeof(keyDescriptions) / sizeof(keyDescriptions[0]);
    DGuiApplicationHelper::ColorType type = DGuiApplicationHelper::instance()->themeType();
    for (int i = 0; i < count; ++i) {
        const KeyDescription *desc = keyDescriptions + i;
        DPushButton *button;

        if (desc->text.isEmpty()) {
            button = createSpecialKeyButton(desc->button);
        } else {
            button = new TextButton(desc->text);
        }
        DPalette pa = button->palette();
        if (type == 0)
            type = DGuiApplicationHelper::instance()->themeType();
        if (type == 2){
            if (button->text() == "=") {
                pa.setColor(DPalette::Shadow, QColor(0,129,255));
                pa.setColor(DPalette::ButtonText, Qt::white);
                pa.setColor(DPalette::Light, QColor(0,129,255));
                pa.setColor(DPalette::Dark, QColor(0,129,255));
            } else {
                pa.setColor(DPalette::Shadow, QColor(17,17,17));
                pa.setColor(DPalette::ButtonText, Qt::white);
                pa.setColor(DPalette::Light, QColor(17,17,17));
                pa.setColor(DPalette::Dark, QColor(17,17,17));
            }
            button->setPalette(pa);
        } else {
            if (button->text() == "=") {
                pa.setColor(DPalette::Shadow, QColor(0,129,255));
                pa.setColor(DPalette::ButtonText, Qt::white);
                pa.setColor(DPalette::Light, QColor(0,129,255));
                pa.setColor(DPalette::Dark, QColor(0,129,255));
            } else {
                pa.setColor(DPalette::Shadow, Qt::white);
                pa.setColor(DPalette::ButtonText, Qt::black);
                pa.setColor(DPalette::Light, QColor(255,255,255));
                pa.setColor(DPalette::Dark, QColor(255,255,255));
            }
            button->setPalette(pa);
        }

        m_layout->addWidget(button, desc->row, desc->column);
        const QPair<DPushButton *, const KeyDescription *> hashValue(button, desc);
        m_keys.insert(desc->button, hashValue);

        connect(button, &DPushButton::clicked, m_mapper, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));
        m_mapper->setMapping(button, desc->button);
    }
}

void BasicKeypad::initUI()
{
    QHashIterator<Buttons, QPair<DPushButton *, const KeyDescription *>> i(m_keys);

    while (i.hasNext()) {
        i.next();
        i.value().first->setFocusPolicy(Qt::NoFocus);
    }

    button(Key_Div)->setObjectName("SymbolButton");
    button(Key_Mult)->setObjectName("SymbolButton");
    button(Key_Min)->setObjectName("SymbolButton");
    button(Key_Plus)->setObjectName("SymbolButton");
    button(Key_Equals)->setObjectName("EqualButton");

    this->setContentsMargins(12,0,13,0);
}

void BasicKeypad::buttonThemeChanged(int type)
{
    if (type == 0)
        type = DGuiApplicationHelper::instance()->themeType();
    if (type == 1) {
        QHash<Buttons, QPair<DPushButton *, const KeyDescription *>>::const_iterator iter1 = m_keys.constBegin();
        while(iter1 != m_keys.constEnd()) {
            DPushButton *button = iter1.value().first;
            DPalette pa = button->palette();
            if (button->text() == "=") {
                pa.setColor(DPalette::Shadow, QColor(0,129,255));
                pa.setColor(DPalette::ButtonText, Qt::white);
                pa.setColor(DPalette::Background, QColor(0,129,255));
            } else {
                pa.setColor(DPalette::Shadow, Qt::white);
                pa.setColor(DPalette::ButtonText, Qt::black);
                pa.setColor(DPalette::Light, QColor(255,255,255));
                pa.setColor(DPalette::Dark, QColor(255,255,255));
            }
            button->setPalette(pa);
            ++iter1;
        }
    } else {
        QHash<Buttons, QPair<DPushButton *, const KeyDescription *>>::const_iterator iter1 = m_keys.constBegin();
        while(iter1 != m_keys.constEnd()) {
            DPushButton *button = iter1.value().first;
            DPalette pa = button->palette();
            if (button->text() == "=") {
                pa.setColor(DPalette::Shadow, QColor(0,129,255));
                pa.setColor(DPalette::ButtonText, Qt::white);
                pa.setColor(DPalette::Background, QColor(0,129,255));
            } else {
                pa.setColor(DPalette::Shadow, QColor(17,17,17));
                pa.setColor(DPalette::ButtonText, Qt::white);
                pa.setColor(DPalette::Light, QColor(17,17,17));
                pa.setColor(DPalette::Dark, QColor(17,17,17));
            }
            button->setPalette(pa);
            ++iter1;
        }
    }
}

void BasicKeypad::handleThemeChanged()
{
    IconButton *btn = static_cast<IconButton *>(button(Key_Backspace));
    btn->setIcon(QString(":/images/delete_light_normal.svg"));
}
