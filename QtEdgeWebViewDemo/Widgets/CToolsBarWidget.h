#ifndef __CTOOLSBARWIDGET_H__
#define __CTOOLSBARWIDGET_H__

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>

class CToolsBarWidget : public QWidget
{
    Q_OBJECT;
    Q_DISABLE_COPY(CToolsBarWidget);

private:
    class QLimitePrivateSignal {};

public:
    explicit CToolsBarWidget(QWidget *parent = nullptr);
    ~CToolsBarWidget();

Q_SIGNALS:
    void signalNative(const QString& str, QLimitePrivateSignal);

private:
    void InitUI();
    void CreateData();
    void CreateConnection();

private:
    QLineEdit* m_pLineEdit = nullptr;
    QPushButton* m_pButton = nullptr;
    QHBoxLayout* m_pLayout = nullptr;
};

#endif // __CTOOLSBARWIDGET_H__