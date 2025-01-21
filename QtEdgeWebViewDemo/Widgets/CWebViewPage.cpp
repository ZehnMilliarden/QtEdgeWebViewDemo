#include "CWebViewPage.h"

CWebViewPage::CWebViewPage(QWidget* parent)
    : QWidget(parent)
{
    InitUI();
}

CWebViewPage::~CWebViewPage()
{
}

void CWebViewPage::InitUI()
{
    CreateData();
    CreateConnection();
}

bool CWebViewPage::CreateData()
{
    m_pLayout = new QVBoxLayout(this);
    setLayout(m_pLayout);

    m_pToolsBarWidget = new CToolsBarWidget(this);
    m_pToolsBarWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_pLayout->addWidget(m_pToolsBarWidget);

    m_pEdgeWebWidget = new CEdgeWebWidget(this);
    m_pEdgeWebWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_pLayout->addWidget(m_pEdgeWebWidget);
    return true;
}

bool CWebViewPage::CreateConnection()
{
    QObject::connect(m_pToolsBarWidget, &CToolsBarWidget::signalNative, m_pEdgeWebWidget, &CEdgeWebWidget::Navigate);
    return true;
}

void CWebViewPage::SetEnvironment(const wil::com_ptr<ICoreWebView2Environment>& pEnv)
{
    if (m_pEdgeWebWidget)
    {
        m_pEdgeWebWidget->SetEnvironment(pEnv);
    }
}
