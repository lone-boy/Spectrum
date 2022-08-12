//
// Created by jcc on 22-8-12.
//

// You may need to build the project (run Qt uic code generator) to get "ui_selectNumber.h" resolved

#include "selectnumber.h"

selectnumber::selectnumber(QWidget *parent)
: QWidget(parent)
{
    _m_maxRange = 999;
    _m_minRange = 0;
    m_currentValue = 0;
    isDragging=0;
    m_deviation=0;
    m_numSize=3;
    isMiddle=false;
    m_prefix="";
    m_suffix="";

    homingAni  = new QPropertyAnimation(this,""); //创建一个动画类
    homingAni->setDuration(300); //设置动画持续时间
    homingAni->setEasingCurve(QEasingCurve::OutQuad); //设置动画的缓动曲线，这里OutQuad是二次函数缓和曲线，减速到零速度

    connect(homingAni,&QPropertyAnimation::finished,this,&selectnumber::slotChoseFinshed);
}

selectnumber::~selectnumber()
{

}
//设置范围
void selectnumber::setRange(int min, int max)
{
    _m_minRange = min;
    _m_maxRange = max;
    if(m_currentValue < min) //如果选中的当前值小于最小值，就等于最小值，不会再减了
    {
        m_currentValue = min;
    }
    if(m_currentValue > max) //最大值同理
    {
        m_currentValue = max;
    }
    //计算字符尺寸
    m_numSize = 3;
    int temp = _m_maxRange;
    while(temp > 0)
    {
        temp /= 10;
        m_numSize++;
    }
    update(); //重绘此组件，需要进行重绘时,要使用update

}
//获取当前值
int selectnumber::readValue()
{
    return m_currentValue;
}

QString selectnumber::getValueStr()
{
    QString strValue;
    if(m_currentValue < 10){
        strValue="00";
    }
    else if(m_currentValue < 100 && m_currentValue >=10){
        strValue="0";
    }
    strValue+=QString::number(m_currentValue);
    return strValue;
}
//设置显示格式
void selectnumber::setFormat(QString prefix, QString suffix)
{
    m_prefix=prefix;
    m_suffix=suffix;
}
//设置当前显示
void selectnumber::setCurValue(int Value)
{
    //判断是否在有效区间内
    if(Value > _m_maxRange)
    {
        Value=_m_maxRange;
    }
    else if(Value < _m_minRange)
    {
        Value=_m_minRange;
    }
    m_currentValue=Value;
    if(this->isVisible())
    {
        update();
    }
}
//鼠标按下事件
void selectnumber::mousePressEvent(QMouseEvent *event)
{
    isDragging = true; //鼠标是否按下的标志位，布尔类型
    m_mouseSrcPos = event->pos().y(); //鼠标按下时候的y轴作标记录下来

    QWidget::mousePressEvent(event);
}
//鼠标移动事件
void selectnumber::mouseMoveEvent(QMouseEvent *event)
{
    if(isDragging)
    {
        //数值到边界时，阻止继续往对应方向移动
        if((m_currentValue == _m_minRange && event->pos().y() >= m_mouseSrcPos) ||
           (m_currentValue == _m_maxRange && event->pos().y() <= m_mouseSrcPos))
            return;

        m_deviation = event->pos().y() - m_mouseSrcPos; //垂直偏移量 = 现在的坐标 - 开始的作标

        //若移动速度过快时进行限制
        if(m_deviation > (height()-1)/5)
        {
            m_deviation = (height()-1)/5;
        }

        else if(m_deviation < -(height()-1)/5)
        {
            m_deviation = -(height()-1)/5;
        }
        update();
    }

    QWidget::mouseMoveEvent(event);
}

void selectnumber::wheelEvent(QWheelEvent *event) {
    if(event->delta() > 0){
        /*  */
        if(m_currentValue == _m_minRange)
            return;

        m_currentValue -= (int)(0.1*event->delta());

    }
    else{
        if(m_currentValue == _m_maxRange)
            return;

        m_currentValue += (int)(0.1*event->delta()*-1);
    }
    m_currentValue = m_currentValue > _m_maxRange? _m_maxRange:m_currentValue;
    m_currentValue = m_currentValue < _m_minRange? _m_minRange:m_currentValue;

    update();
    emit send_value_changed();
    QWidget::wheelEvent(event);
}

//鼠标松开事件
void selectnumber::mouseReleaseEvent(QMouseEvent *event)
{
    if(isDragging) //如果鼠标松开了，那么还原一下鼠标按下标志位
    {
        homing();
        isDragging = false;
        update();
    }

    QWidget::mouseReleaseEvent(event);
}
//绘图事件
void selectnumber::paintEvent(QPaintEvent *m_painter)
{
    QPainter painter(this); //创建画家类，指定绘图设备，也就是在哪画
    painter.setRenderHint(QPainter::Antialiasing, true); //反走样，就是抗锯齿

    int Width = width()-1; //设置宽高
    int Height = height()-1;

    if(m_deviation >= Height/5 && m_currentValue > _m_minRange) //偏移量大于1/5 高的时候，数字减一
    {
        m_mouseSrcPos += Height/5; //鼠标起始位置重新设置，即加上1/5的高度
        m_deviation -= Height/5; //偏移量重新设置，即减去1/5的高度
        m_currentValue--;
    }
    if(m_deviation <= -Height/5 && m_currentValue < _m_maxRange) //同理，数字加一
    {
        m_mouseSrcPos -= Height/5;
        m_deviation += Height/5;
        m_currentValue++;
    }

    //中间数字
    paintNum(painter,m_currentValue,m_deviation,isMiddle=1); //将选中数字画到中间

    //两侧数字1
    if(m_currentValue != _m_minRange) //选中的数字不是最小，不是最大，那么就有两侧数字，然后画出两侧数字
        paintNum(painter,m_currentValue-1,m_deviation-Height*2/10,isMiddle=0);
    if(m_currentValue != _m_maxRange)
        paintNum(painter,m_currentValue+1,m_deviation+Height*2/10,isMiddle=0);

    //两侧数字2,超出则不显示
    if(m_deviation >= 0 && m_currentValue-2 >= _m_minRange)
        paintNum(painter,m_currentValue-2,m_deviation-Height*4/10,isMiddle=0);
    if(m_deviation <= 0 && m_currentValue+2 <= _m_maxRange)
        paintNum(painter,m_currentValue+2,m_deviation+Height*4/10,isMiddle=0);

    //画边框，中间数字两侧的边框
    painter.setPen(QPen(QColor(5,39,175,120),4));
    painter.drawLine(0,Height/8*3,Width,Height/8*3);
    painter.drawLine(0,Height/8*5,Width,Height/8*5);

    QWidget::paintEvent(m_painter);
}
//画数字函数
void selectnumber::paintNum(QPainter &painter, int num, int deviation, bool isMiddle)
{
    int Width = this->width()-1;
    int Height = this->height()-1;

    int size = (Height - qAbs(deviation))/m_numSize; //qAbs 返回输入参数对应类型的绝对值。
    int transparency = 255-510*qAbs(deviation)/Height; //设置透明度
    int height = Height/2-3*qAbs(deviation)/5;
    int y = Height/2+deviation-height/2;
    QFont font;
    font.setPixelSize(size); //设置像素大小
    painter.setFont(font); //设置字体
    if(isMiddle)
    {
        painter.setPen(QColor(34,215,187,transparency)); //设置画笔,基色
    }
    else
    {
        painter.setPen(QColor(0,0,0,transparency)); //设置画笔，黑色
    }
    QString str_date;
    if(num<=9)
    {
        str_date=QString("00")+QString::number(num);
    }
    else if(num <= 99)
    {
        str_date=QString("0")+QString::number(num);

    }
    else
    {
        str_date=QString::number(num);
    }
    str_date=m_prefix+str_date+m_suffix;
    painter.drawText(QRectF(0,y,Width,height), //画文本，参数：QRectF参数：位置xy，长宽大小；对齐方式，中间对齐；内容
                     Qt::AlignCenter,
                     str_date);

}

//使选中的数字回到屏幕中间
void selectnumber::homing()
{
    //将数字矫正到中心
    if(m_deviation > height()/20)
    {
        homingAni->setStartValue((height()-1)/8-m_deviation);
        homingAni->setEndValue(0);
        m_currentValue--;
    }
    else if(m_deviation > -(height())/20)
    {
        homingAni->setStartValue(m_deviation);
        homingAni->setEndValue(0);
    }
    else if(m_deviation < -(height())/20)
    {
        homingAni->setStartValue(-(height()-1)/8-m_deviation);
        homingAni->setEndValue(0);
        m_currentValue++;
    }
    m_deviation=0;

    homingAni->start(); //开始动画
}
//动画结束
void selectnumber::slotChoseFinshed()
{
//    emit currentValueChanged(m_currentValue); //发送当前数值改变信号

    emit send_value_changed();
}