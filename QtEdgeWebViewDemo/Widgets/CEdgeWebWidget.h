#ifndef __CEDGEWEBWIDGET_H__
#define __CEDGEWEBWIDGET_H__

#include <QWidget>
#include <QHBoxLayout>
#include <Windows.h>

#include <wil/com.h>
#include <WebView2.h>

using namespace Microsoft::WRL;

class CEdgeWebWidget 
    : public QWidget
{
    Q_OBJECT;
    Q_DISABLE_COPY(CEdgeWebWidget);

public:
    explicit CEdgeWebWidget(QWidget* parent = nullptr);
    ~CEdgeWebWidget();

    bool Navigate(const QString& url);
    void SetEnvironment(const wil::com_ptr<ICoreWebView2Environment>& pEnv);

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    void InitUI();
    bool CreateData();
    bool CreateConnection();
    bool CreateWebView(const QString& url);

private:
    wil::com_ptr<ICoreWebView2> m_pWebview = nullptr;
    wil::com_ptr<ICoreWebView2Controller> m_pWebViewController = nullptr;
    wil::com_ptr<ICoreWebView2Environment> m_pEnv = nullptr;
};

#endif // __CEDGEWEBWIDGET_H__