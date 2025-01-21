#ifndef __CWEBVIEWPAGE_H__
#define __CWEBVIEWPAGE_H__

#include <QWidget>

#include "CEdgeWebWidget.h"
#include "CToolsBarWidget.h"

class CWebViewPage : public QWidget
{
    Q_OBJECT;
    Q_DISABLE_COPY(CWebViewPage);

public:
    explicit CWebViewPage(QWidget*parent = nullptr);
    ~CWebViewPage();

private:
    void InitUI();
    bool CreateData();
    bool CreateConnection();

public:
    void SetEnvironment(const wil::com_ptr<ICoreWebView2Environment>& pEnv);

private:
    QVBoxLayout* m_pLayout = nullptr;
    CToolsBarWidget* m_pToolsBarWidget = nullptr;
    CEdgeWebWidget* m_pEdgeWebWidget = nullptr;
};

#endif //__CWEBVIEWPAGE_H__