﻿#include "robot.h"


#include <QMimeData>
#include <QGraphicsSceneDragDropEvent>
#include <QPainter>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QDebug>

RobotPart::RobotPart(QGraphicsItem* parent)
	:QGraphicsObject(parent),mColor(Qt::lightGray), mbDrag(false)
{
	// set item accept drop
	setAcceptDrops(true);
}

void RobotPart::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
	qDebug() << "dragEnterEvent ---------------- " << mColor;

	if (event->mimeData()->hasColor())
	{
		event->setAccepted(true);
		mbDrag = true;
		update();
	}
	else
	{
		// event stop here.
		event->setAccepted(false);
	}
}

void RobotPart::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
	mbDrag = false;
}

void RobotPart::dropEvent(QGraphicsSceneDragDropEvent *event)
{
	mbDrag = false;

	if (event->mimeData()->hasColor())
	{
		mColor = qvariant_cast<QColor>(event->mimeData()->colorData());
		qDebug() << "color " << mColor;
	}
	update();
}

//---

Robot::Robot()
{
	setFlag(GraphicsItemFlag::ItemHasNoContents);

	QGraphicsObject *torsoItem = new RobotTorso(this);
	QGraphicsObject *headItem = new RobotHead(torsoItem);
	QGraphicsObject *upperLeftArmItem = new RobotLimb(torsoItem);
	QGraphicsObject *lowerLeftArmItem = new RobotLimb(upperLeftArmItem);
	QGraphicsObject *upperRightArmItem = new RobotLimb(torsoItem);
	QGraphicsObject *lowerRightArmItem = new RobotLimb(upperRightArmItem);
	QGraphicsObject *upperRightLegItem = new RobotLimb(torsoItem);
	QGraphicsObject *lowerRightLegItem = new RobotLimb(upperRightLegItem);
	QGraphicsObject *upperLeftLegItem = new RobotLimb(torsoItem);
	QGraphicsObject *lowerLeftLegItem = new RobotLimb(upperLeftLegItem);

	headItem->setPos(0, -18);


	upperLeftArmItem->setPos(-15, -10);
	lowerLeftArmItem->setPos(30, 0);
	upperRightArmItem->setPos(15, -10);
	lowerRightArmItem->setPos(30, 0);
	upperRightLegItem->setPos(10, 32);
	lowerRightLegItem->setPos(30, 0);
	upperLeftLegItem->setPos(-10, 32);
	lowerLeftLegItem->setPos(30, 0);
	
	QParallelAnimationGroup *animation = new QParallelAnimationGroup(this);

    QPropertyAnimation *headAnimation = new QPropertyAnimation(headItem, "rotation");
    headAnimation->setStartValue(60);
    headAnimation->setEndValue(-20);
    QPropertyAnimation *headScaleAnimation = new QPropertyAnimation(headItem, "scale");
    headScaleAnimation->setEndValue(1.8);
    animation->addAnimation(headAnimation);
    animation->addAnimation(headScaleAnimation);

    QPropertyAnimation *upperLeftArmAnimation = new QPropertyAnimation(upperLeftArmItem, "rotation");
    upperLeftArmAnimation->setStartValue(190);
    upperLeftArmAnimation->setEndValue(180);
    animation->addAnimation(upperLeftArmAnimation);

	
    QPropertyAnimation *lowerLeftArmAnimation = new QPropertyAnimation(lowerLeftArmItem, "rotation");
    lowerLeftArmAnimation->setStartValue(50);
    lowerLeftArmAnimation->setEndValue(10);
    animation->addAnimation(lowerLeftArmAnimation);
	
    QPropertyAnimation *upperRightArmAnimation = new QPropertyAnimation(upperRightArmItem, "rotation");
    upperRightArmAnimation->setStartValue(300);
    upperRightArmAnimation->setEndValue(310);
    animation->addAnimation(upperRightArmAnimation);

    QPropertyAnimation *lowerRightArmAnimation = new QPropertyAnimation(lowerRightArmItem, "rotation");
    lowerRightArmAnimation->setStartValue(0);
    lowerRightArmAnimation->setEndValue(-70);
    animation->addAnimation(lowerRightArmAnimation);

    QPropertyAnimation *upperLeftLegAnimation = new QPropertyAnimation(upperLeftLegItem, "rotation");
    upperLeftLegAnimation->setStartValue(150);
    upperLeftLegAnimation->setEndValue(80);
    animation->addAnimation(upperLeftLegAnimation);

    QPropertyAnimation *lowerLeftLegAnimation = new QPropertyAnimation(lowerLeftLegItem, "rotation");
    lowerLeftLegAnimation->setStartValue(70);
    lowerLeftLegAnimation->setEndValue(10);
    animation->addAnimation(lowerLeftLegAnimation);

    QPropertyAnimation *upperRightLegAnimation = new QPropertyAnimation(upperRightLegItem, "rotation");
    upperRightLegAnimation->setStartValue(40);
    upperRightLegAnimation->setEndValue(120);
    animation->addAnimation(upperRightLegAnimation);

    QPropertyAnimation *lowerRightLegAnimation = new QPropertyAnimation(lowerRightLegItem, "rotation");
    lowerRightLegAnimation->setStartValue(10);
    lowerRightLegAnimation->setEndValue(50);
    animation->addAnimation(lowerRightLegAnimation);

    QPropertyAnimation *torsoAnimation = new QPropertyAnimation(torsoItem, "rotation");
    torsoAnimation->setStartValue(5);
    torsoAnimation->setEndValue(-20);
    animation->addAnimation(torsoAnimation);

    for (int i = 0; i < animation->animationCount(); ++i) {
        QPropertyAnimation *anim = qobject_cast<QPropertyAnimation *>(animation->animationAt(i));
        anim->setEasingCurve(QEasingCurve::SineCurve);
        anim->setDuration(2000);
    }

    animation->setLoopCount(-1);
    animation->start();
}

void Robot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */)
{

}

QRectF Robot::boundingRect() const
{
	return QRectF();
}

//---

RobotTorso::RobotTorso(QGraphicsItem* parent/*=0*/)
	:RobotPart(parent)
{

}

void RobotTorso::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */)
{

	painter->setBrush(mbDrag ? mColor.lighter(130) : mColor);
	painter->drawRoundedRect(-20, -20, 40, 60, 25, 25,Qt::RelativeSize);
	painter->drawEllipse(-25, -20, 20, 20);
	painter->drawEllipse(5, -20, 20, 20);
	painter->drawEllipse(-20, 22, 20, 20);
	painter->drawEllipse(0, 22, 20, 20);

}

QRectF RobotTorso::boundingRect() const
{
	return QRectF(-30, -20, 60, 60);
}

RobotLimb::RobotLimb(QGraphicsItem* parent /*= 0*/)
	:RobotPart(parent)
{

}

void RobotLimb::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */)
{
	painter->setBrush(mbDrag ? mColor.lighter(130) : mColor);
	painter->drawRoundedRect(boundingRect(), 50, 50, Qt::RelativeSize);
	painter->drawEllipse(-5, -5, 10, 10);
}

QRectF RobotLimb::boundingRect() const
{
	return QRectF(-5, -5, 40, 10);
}

RobotHead::RobotHead(QGraphicsItem* parent /*= 0*/)
	:RobotPart(parent)
{

}

void RobotHead::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */)
{
	if (mHeadImg.isNull()) {
		painter->setBrush(mbDrag ? mColor.lighter(130) : mColor);
		painter->drawRoundedRect(-10, -30, 20, 30, 25, 25, Qt::RelativeSize);
		painter->setBrush(Qt::white);
		painter->drawEllipse(-7, -3 - 20, 7, 7);
		painter->drawEllipse(0, -3 - 20, 7, 7);
		painter->setBrush(Qt::black);
		painter->drawEllipse(-5, -1 - 20, 2, 2);
		painter->drawEllipse(2, -1 - 20, 2, 2);
		painter->setPen(QPen(Qt::black, 2));
		painter->setBrush(Qt::NoBrush);
		painter->drawArc(-6, -2 - 20, 12, 15, 190 * 16, 160 * 16);
	}
	else 
	{
		painter->scale(.2272, .2824);
		painter->drawPixmap(QPointF(-15 * 4.4, -50 * 3.54), mHeadImg);
	}
}

QRectF RobotHead::boundingRect() const
{
	return QRectF(-15, -50, 30, 50);
}

void RobotHead::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
	if (event->mimeData()->hasImage())
	{
		event->setAccepted(true);
		mbDrag = true;
		update();
	}
	else
	{
		RobotPart::dragEnterEvent(event);
	}
}

void RobotHead::dropEvent(QGraphicsSceneDragDropEvent *event)
{
	if (event->mimeData()->hasImage())
	{
		mbDrag = false;
		mHeadImg = qvariant_cast<QPixmap>(event->mimeData()->imageData());
		update();
	}
	else
	{
		RobotPart::dropEvent(event);
	}

}

