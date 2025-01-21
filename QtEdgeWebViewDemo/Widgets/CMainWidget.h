#ifndef __CMAINWIDGET_H__
#define __CMAINWIDGET_H__

#include <QWidget>
#include <QHBoxLayout>
#include <QTabWidget>

#include <wil/com.h>
#include <WebView2.h>
#include <wrl.h>

class CMainWidget : public QWidget
{
    Q_OBJECT;
    Q_DISABLE_COPY(CMainWidget);

public:
    explicit CMainWidget(QWidget *parent = nullptr);
    ~CMainWidget();

    void ShowCenter();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void InitUI();
    bool CreateConnect();
    bool CreateData();
    bool CreateWebEnvironment();

private:
    QTabWidget      *m_pTabWidget = nullptr;
    wil::com_ptr<ICoreWebView2Environment> m_pWebEnvironment = nullptr;
};

#endif // __CMAINWIDGET_H__