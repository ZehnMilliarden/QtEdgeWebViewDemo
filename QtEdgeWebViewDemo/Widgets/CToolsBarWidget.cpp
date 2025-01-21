#include "CToolsBarWidget.h"

CToolsBarWidget::CToolsBarWidget(QWidget* parent)
    : QWidget(parent)
{
    setObjectName("CToolsBarWidget");
    InitUI();
}

CToolsBarWidget::~CToolsBarWidget()
{
}

void CToolsBarWidget::InitUI()
{
    CreateData();
    CreateConnection();
}

void CToolsBarWidget::CreateData()
{
    setFixedHeight(50);

    m_pLayout = new QHBoxLayout(this);
    setLayout(m_pLayout);

    m_pLineEdit = new QLineEdit(this);
    m_pLineEdit->setPlaceholderText("url...");
    m_pLayout->addWidget(m_pLineEdit, 1, Qt::AlignLeft);
    m_pLineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_pButton = new QPushButton(this);
    m_pButton->setText("Go");
    m_pLayout->addWidget(m_pButton, 0, Qt::AlignLeft);
    m_pButton->setFixedWidth(100);
    m_pButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
}
                                                        
void CToolsBarWidget::CreateConnection()
{
    QObject::connect(m_pButton, &QPushButton::clicked, this, [this](bool bChecked) {
            const QString strNewUrl = m_pLineEdit->text();
            emit signalNative(strNewUrl, QLimitePrivateSignal());
        });

    QObject::connect(m_pLineEdit, &QLineEdit::returnPressed, this, [this]() {
        const QString strNewUrl = m_pLineEdit->text();
            emit signalNative(strNewUrl, QLimitePrivateSignal());
        });
}
