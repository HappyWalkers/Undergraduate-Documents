#ifndef T9WIDGET_H
#define T9WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QButtonGroup>
#include <QString>
#include <QStringList>

namespace Ui {
    class T9Widget;
}

namespace T9MAP {
    typedef struct pyitem_t {
        const char *T9;
        const char *PY;
        const char *HZ;
    } pyitem;

    typedef struct t9item_t {
        const char *T9;
        int count;
        const pyitem *pyTab;
    } t9item;
}
typedef const T9MAP::t9item *PCT9ITEM;
typedef const T9MAP::pyitem *PCPYITEM;

class T9Widget : public QWidget
{
    Q_OBJECT

public:
    explicit T9Widget(QWidget *recver = 0, QWidget *parent = 0);
    ~T9Widget();
    typedef enum { english = 0, chinese, syssymbol, number, METHODMAX } INPUTMETHOD;

signals:
    void newString(const QString &str);

public slots:
    void changeRecver(QWidget *recver) {
        msgReceiver = recver;
        setFocusProxy(recver);
    }
    void setMethod(INPUTMETHOD method) {
    	currentMethod = method;
    	changeUI();
    }
    void setMethodEnabled(INPUTMETHOD method, bool enable) {
        if(method >= METHODMAX)
            return;
        if(method < 0)
            return;
        methodEnableList[method] = enable;
        if(!enable && (currentMethod == method))
            switchMethod();
    }
    void setAllMethodEnabled(bool enable) {
        for(unsigned int i = 0; i < sizeof(methodEnableList)/ sizeof(methodEnableList[0]); i++)
            methodEnableList[i] = enable;
        changeUI();
    }

protected:
    void keyPressEvent(QKeyEvent *ev);

    bool isMoving;
    QPoint lastPnt;
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);

private slots:
    void on_pyPgDn_clicked();
    void on_pyPgUp_clicked();
    void on_jingBtn_clicked();
    void on_starBtn_clicked();
    void on_enterBtn_clicked();
    void on_spaceBtn_clicked();
    void on_backSpaceBtn_clicked();
    void on_methodBtn_clicked();
    void on_pgDnBtn_clicked();
    void on_pgUpBtn_clicked();
    void onNumberClicked(int id);
    void onPyClicked(int id);
    void onHzClicked(int id);

private:
    // UIs
    Ui::T9Widget *ui;
    QIcon btnIcon[2][10];
    QButtonGroup *pyGroup;                      // 待选拼音列表
    QButtonGroup *hzGroup;                      // 待选汉字列表
    QButtonGroup *numberGroup;                  // 数字按键列表
    void changeUI();
    enum { ReloadNumberString = 0x01, ReloadPinYin = 0x02, ReloadUI = 0x04 };
    void updateT9UI(int type = ReloadUI);
    void switchMethod();
    void pageUp();
    void pageDown();
    void moveLeft();
    void moveRight();

    void pyPageUp();
    void pyPageDown();
    void pyMoveLeft();
    void pyMoveRight();

    bool isZoomIn;

private:
    // Data Solutions
    INPUTMETHOD currentMethod;
    bool methodEnableList[METHODMAX];

    QString inputString;

    PCT9ITEM readyPYList;
//    PYIdxList readyPYList;
    QStringList readyCharList;

    int pyMaxCount;
    int pyPageCount;
    int pyCurrentPage;

    int maxCount;
    int pageCount;
    int currentPage;
    int currentPY;
    int confirmHZ;

    QWidget *msgReceiver;
};

#endif // T9WIDGET_H
