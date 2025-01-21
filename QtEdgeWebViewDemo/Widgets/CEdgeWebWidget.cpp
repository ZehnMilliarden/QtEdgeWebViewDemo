#include "CEdgeWebWidget.h"

#include <wrl.h>

CEdgeWebWidget::CEdgeWebWidget(QWidget* parent)
    : QWidget(parent)
{
    InitUI();
}

CEdgeWebWidget::~CEdgeWebWidget()
{
}

bool CEdgeWebWidget::Navigate(const QString& url)
{
    if (!m_pWebview)
    {
        return CreateWebView(url);
    }

    m_pWebview->Navigate(url.toStdWString().c_str());
    return true;
}

void CEdgeWebWidget::SetEnvironment(const wil::com_ptr<ICoreWebView2Environment>& pEnv)
{
    m_pEnv = pEnv;
}

void CEdgeWebWidget::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    if (m_pWebViewController)
    {
        RECT bounds{ 0, 0, width(), height() };
        m_pWebViewController->put_Bounds(bounds);
    }
}

void CEdgeWebWidget::InitUI()
{
    do
    {
        if (!CreateData())
        {
            break;
        }

        if (!CreateConnection())
        {
            break;
        }

    } while (false);
}

bool CEdgeWebWidget::CreateData()
{
    return true;
}

bool CEdgeWebWidget::CreateConnection()
{
    return true;
}

bool CEdgeWebWidget::CreateWebView(const QString& url)
{
    if (m_pEnv)
    {
        HWND hwnd = reinterpret_cast<HWND>(winId());
        HRESULT hr = ::IsWindow(hwnd) ? S_OK : E_FAIL;
        if (SUCCEEDED(hr))
        {
            m_pEnv->CreateCoreWebView2Controller(hwnd,
                Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(
                    [this, url](HRESULT result, ICoreWebView2Controller* controller) -> HRESULT {
                        m_pWebViewController = controller;
                        controller->get_CoreWebView2(&m_pWebview);

                        wil::com_ptr<ICoreWebView2Settings> settings;
                        m_pWebview->get_Settings(&settings);
                        settings->put_IsScriptEnabled(TRUE);
                        settings->put_AreDefaultScriptDialogsEnabled(TRUE);
                        settings->put_IsWebMessageEnabled(TRUE);

                        RECT bounds{ 0, 0, width(), height() };
                        m_pWebViewController->put_Bounds(bounds);

                        EventRegistrationToken token;
                        m_pWebview->add_NavigationStarting(Callback<ICoreWebView2NavigationStartingEventHandler>(
                            [](ICoreWebView2* webview, ICoreWebView2NavigationStartingEventArgs* args) -> HRESULT {
                                wil::unique_cotaskmem_string uri;
                                args->get_Uri(&uri);
                                std::wstring source(uri.get());
                                if (source.substr(0, 4) != L"file"
                                    && source.substr(0, 4) != L"http") {
                                    args->put_Cancel(true);
                                }
                                return S_OK;
                            }).Get(), &token);

                        m_pWebview->Navigate(url.toStdWString().c_str());

                        return S_OK;
                    }
                ).Get());
        }
    }

    return true;
}
