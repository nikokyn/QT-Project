#ifndef STYLE_H
#define STYLE_H

#include <QAbstractItemModel>

class style : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit style(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
};

class MyPushButton : public QPushButton
{
       Q_OBJECT
       Q_PROPERTY( QColor   BackgroundColor    READ backgroundColor  WRITE setBackgroundColor DESIGNABLE true )

public:
      MyPushButton( QWidget* parent = 0 ) : QPushButton( parent )
      {
          this->setText("Text");

           m_Animation = new QPropertyAnimation(this, "BackgroundColor", this);
           m_Animation->setDuration( 500 );
           m_Animation->setEasingCurve( QEasingCurve::OutQuad );

           m_BackgroundColor = Qt::transparent;
           this->setBackgroundColor( Qt::white ); //initial color
      }

       QColor backgroundColor() const
       {
            return m_BackgroundColor;
       }

       void setBackgroundColor( const QColor & color )
       {
           if( m_BackgroundColor != color )
           {
               m_BackgroundColor = color;
              this->setStyleSheet( QString("MyPushButton { border: 1px solid black; background-color: %1; }").arg(color.name()) );
            }
       }

protected:
       virtual void enterEvent( QEvent * event )
       {
            QPushButton::enterEvent(event);

            if( m_Animation->state() == QAbstractAnimation::Running )
                m_Animation->stop();

            m_Animation->setEndValue( QColor(Qt::red) );
            m_Animation->start();
       }

       virtual void leaveEvent( QEvent* event )
       {
            QPushButton::leaveEvent(event);

            QVariant currentColor = m_Animation->currentValue();

            if( m_Animation->state() == QAbstractAnimation::Running )
                m_Animation->stop();

            m_Animation->setEndValue( QColor(Qt::white) );
            m_Animation->start();
       }

       QPropertyAnimation*     m_Animation;
       QColor                   m_BackgroundColor;
};
#endif // STYLE_H
