#include "CMainWidget.h"

#include <QApplication>
#include <QScreen>

#include "CWebViewPage.h"

CMainWidget::CMainWidget(QWidget* parent)
    : QWidget(parent)
{
    setObjectName("CMainWidget");
    InitUI();
}

CMainWidget::~CMainWidget()
{
}

void CMainWidget::ShowCenter()
{
    QScreen* screen = QApplication::screens().at(0);
    QRect screenGeometry = screen->geometry();
    int width = screenGeometry.width() / 2;
    int height = screenGeometry.height() / 2;
    resize(width, height);
    int x = (screenGeometry.width() - width) / 2;
    int y = (screenGeometry.height() - height) / 2;
    move(x, y);
    show();
}

void CMainWidget::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    if (m_pTabWidget)
    {
        m_pTabWidget->resize(width(), height());
    }
}

void CMainWidget::InitUI()
{
    CreateWebEnvironment();
    CreateData();
    CreateConnect();
}

bool CMainWidget::CreateConnect()
{
    return false;
}

bool CMainWidget::CreateData()
{
    m_pTabWidget = new QTabWidget(this);
    for (int i = 0; i < 3; ++i)
    {
        CWebViewPage* _pWebViewPage = new CWebViewPage(this);
        if (m_pWebEnvironment)
        {
            _pWebViewPage->SetEnvironment(m_pWebEnvironment);
        }
        _pWebViewPage->setVisible(true);
        m_pTabWidget->addTab(qobject_cast<QWidget*>(_pWebViewPage), QString::number(i));
    }

    return true;
}

bool CMainWidget::CreateWebEnvironment()
{
    
    wchar_t* pszVersion = nullptr;
    HRESULT hr = ::GetAvailableCoreWebView2BrowserVersionString(nullptr, &pszVersion);
    if (!SUCCEEDED(hr) || nullptr == pszVersion)
    {
        return false;
    }

    CoTaskMemFree(pszVersion);
    
    QString strAppDirPath = QCoreApplication::applicationDirPath();
    std::wstring strUserDataPath = strAppDirPath.toStdWString() + L"/UserData";
    hr = ::CreateCoreWebView2EnvironmentWithOptions(nullptr, strUserDataPath.c_str(), nullptr,
        Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
            [this](HRESULT result, ICoreWebView2Environment* env) -> HRESULT {
                m_pWebEnvironment = env;

                if (m_pTabWidget)
                {
                    int nCount = m_pTabWidget->count();
                    for (int i = 0; i < nCount; ++i)
                    {
                        CWebViewPage* _pWebViewPage = qobject_cast<CWebViewPage*>(m_pTabWidget->widget(i));
                        _pWebViewPage->SetEnvironment(m_pWebEnvironment);
                    }
                }

                return S_OK;
            }
        ).Get());

    return SUCCEEDED(hr);
}
