﻿/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Solutions component.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QApplication>
#include <QScrollArea>
#include <QGridLayout>
#include <QLabel>
#include <QIcon>
#include <QMap>

#include "qtpropertymanager.h"
#include "qteditorfactory.h"

#include "qttreepropertybrowser.h"
#include "qtbuttonpropertybrowser.h"
#include "qtgroupboxpropertybrowser.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QWidget *w = new QWidget();

    QtBoolPropertyManager *boolManager = new QtBoolPropertyManager(w);
    QtIntPropertyManager *intManager = new QtIntPropertyManager(w);
    QtStringPropertyManager *stringManager = new QtStringPropertyManager(w);
    QtSizePropertyManager *sizeManager = new QtSizePropertyManager(w);
    QtRectPropertyManager *rectManager = new QtRectPropertyManager(w);
    QtSizePolicyPropertyManager *sizePolicyManager = new QtSizePolicyPropertyManager(w);
    QtEnumPropertyManager *enumManager = new QtEnumPropertyManager(w);
    QtGroupPropertyManager *groupManager = new QtGroupPropertyManager(w);

    QtCheckBoxFactory *checkBoxFactory = new QtCheckBoxFactory(w);
    QtSpinBoxFactory *spinBoxFactory = new QtSpinBoxFactory(w);
    QtSliderFactory *sliderFactory = new QtSliderFactory(w);
    QtScrollBarFactory *scrollBarFactory = new QtScrollBarFactory(w);
    QtLineEditFactory *lineEditFactory = new QtLineEditFactory(w);
    QtEnumEditorFactory *comboBoxFactory = new QtEnumEditorFactory(w);


    QtProperty *item0 = groupManager->addProperty("QMessageBox");

    QtProperty *item1 = stringManager->addProperty("objectName");
    item0->addSubProperty(item1);


    QtProperty *item2 = boolManager->addProperty("enabled");
    item0->addSubProperty(item2);

    QtProperty *item3 = rectManager->addProperty("geometry");
    item0->addSubProperty(item3);

    QtProperty *item4 = sizePolicyManager->addProperty("sizePolicy");
    item0->addSubProperty(item4);

    QtProperty *item5 = sizeManager->addProperty("sizeIncrement");
    item0->addSubProperty(item5);

    QtProperty *item7 = boolManager->addProperty("mouseTracking");
    item0->addSubProperty(item7);

    QtProperty *item8 = enumManager->addProperty("direction");
    QStringList enumNames;
    enumNames << "Up" << "Right" << "Down" << "Left";
    enumManager->setEnumNames(item8, enumNames);
    QMap<int, QIcon> enumIcons;
    enumIcons[0] = QIcon(":/demo/images/up.png");
    enumIcons[1] = QIcon(":/demo/images/right.png");
    enumIcons[2] = QIcon(":/demo/images/down.png");
    enumIcons[3] = QIcon(":/demo/images/left.png");
    enumManager->setEnumIcons(item8, enumIcons);
    item0->addSubProperty(item8);

    QtProperty *item9 = intManager->addProperty("value");
    intManager->setRange(item9, -100, 100);
    item0->addSubProperty(item9);



    QtAbstractPropertyBrowser *browser1 = new QtTreePropertyBrowser();
    browser1->setFactoryForManager(boolManager, checkBoxFactory);
    browser1->setFactoryForManager(intManager, spinBoxFactory);
    browser1->setFactoryForManager(stringManager, lineEditFactory);
    browser1->setFactoryForManager(sizeManager->subIntPropertyManager(), spinBoxFactory);
    browser1->setFactoryForManager(rectManager->subIntPropertyManager(), spinBoxFactory);
    browser1->setFactoryForManager(sizePolicyManager->subIntPropertyManager(), spinBoxFactory);
    browser1->setFactoryForManager(sizePolicyManager->subEnumPropertyManager(), comboBoxFactory);
    browser1->setFactoryForManager(enumManager, comboBoxFactory);

    browser1->addProperty(item0);


    QtAbstractPropertyBrowser *browser2 = new QtTreePropertyBrowser();
    browser2->addProperty(item0);

    QtAbstractPropertyBrowser *browser3 = new QtGroupBoxPropertyBrowser();
    browser3->setFactoryForManager(boolManager, checkBoxFactory);
    browser3->setFactoryForManager(intManager, spinBoxFactory);
    browser3->setFactoryForManager(stringManager, lineEditFactory);
    browser3->setFactoryForManager(sizeManager->subIntPropertyManager(), spinBoxFactory);
    browser3->setFactoryForManager(rectManager->subIntPropertyManager(), spinBoxFactory);
    browser3->setFactoryForManager(sizePolicyManager->subIntPropertyManager(), spinBoxFactory);
    browser3->setFactoryForManager(sizePolicyManager->subEnumPropertyManager(), comboBoxFactory);
    browser3->setFactoryForManager(enumManager, comboBoxFactory);

    browser3->addProperty(item0);

    QScrollArea *scroll3 = new QScrollArea();
    scroll3->setWidgetResizable(true);
    scroll3->setWidget(browser3);

    QtAbstractPropertyBrowser *browser4 = new QtGroupBoxPropertyBrowser();
    browser4->setFactoryForManager(boolManager, checkBoxFactory);
    browser4->setFactoryForManager(intManager, scrollBarFactory);
    browser4->setFactoryForManager(stringManager, lineEditFactory);
    browser4->setFactoryForManager(sizeManager->subIntPropertyManager(), spinBoxFactory);
    browser4->setFactoryForManager(rectManager->subIntPropertyManager(), spinBoxFactory);
    browser4->setFactoryForManager(sizePolicyManager->subIntPropertyManager(), sliderFactory);
    browser4->setFactoryForManager(sizePolicyManager->subEnumPropertyManager(), comboBoxFactory);
    browser4->setFactoryForManager(enumManager, comboBoxFactory);

    browser4->addProperty(item0);

    QScrollArea *scroll4 = new QScrollArea();
    scroll4->setWidgetResizable(true);
    scroll4->setWidget(browser4);

    QtAbstractPropertyBrowser *browser5 = new QtButtonPropertyBrowser();
    browser5->setFactoryForManager(boolManager, checkBoxFactory);
    browser5->setFactoryForManager(intManager, scrollBarFactory);
    browser5->setFactoryForManager(stringManager, lineEditFactory);
    browser5->setFactoryForManager(sizeManager->subIntPropertyManager(), spinBoxFactory);
    browser5->setFactoryForManager(rectManager->subIntPropertyManager(), spinBoxFactory);
    browser5->setFactoryForManager(sizePolicyManager->subIntPropertyManager(), sliderFactory);
    browser5->setFactoryForManager(sizePolicyManager->subEnumPropertyManager(), comboBoxFactory);
    browser5->setFactoryForManager(enumManager, comboBoxFactory);

    browser5->addProperty(item0);

    QScrollArea *scroll5 = new QScrollArea();
    scroll5->setWidgetResizable(true);
    scroll5->setWidget(browser5);

    QGridLayout *layout = new QGridLayout(w);
    QLabel *label1 = new QLabel("Editable Tree Property Browser");
    QLabel *label2 = new QLabel("Read Only Tree Property Browser, editor factories are not set");
    QLabel *label3 = new QLabel("Group Box Property Browser");
    QLabel *label4 = new QLabel("Group Box Property Browser with different editor factories");
    QLabel *label5 = new QLabel("Button Property Browser");
    label1->setWordWrap(true);
    label2->setWordWrap(true);
    label3->setWordWrap(true);
    label4->setWordWrap(true);
    label5->setWordWrap(true);
    label1->setFrameShadow(QFrame::Sunken);
    label2->setFrameShadow(QFrame::Sunken);
    label3->setFrameShadow(QFrame::Sunken);
    label4->setFrameShadow(QFrame::Sunken);
    label5->setFrameShadow(QFrame::Sunken);
    label1->setFrameShape(QFrame::Panel);
    label2->setFrameShape(QFrame::Panel);
    label3->setFrameShape(QFrame::Panel);
    label4->setFrameShape(QFrame::Panel);
    label5->setFrameShape(QFrame::Panel);
    label1->setAlignment(Qt::AlignCenter);
    label2->setAlignment(Qt::AlignCenter);
    label3->setAlignment(Qt::AlignCenter);
    label4->setAlignment(Qt::AlignCenter);
    label5->setAlignment(Qt::AlignCenter);

    layout->addWidget(label1, 0, 0);
    layout->addWidget(label2, 0, 1);
    layout->addWidget(label3, 0, 2);
    layout->addWidget(label4, 0, 3);
    layout->addWidget(label5, 0, 4);
    layout->addWidget(browser1, 1, 0);
    layout->addWidget(browser2, 1, 1);
    layout->addWidget(scroll3, 1, 2);
    layout->addWidget(scroll4, 1, 3);
    layout->addWidget(scroll5, 1, 4);
    w->show();

    return app.exec();
}
