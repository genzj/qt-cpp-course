#ifndef TASK_H
#define TASK_H

#include <QWidget>

namespace Ui {
class Task;
}

class Task : public QWidget
{
    Q_OBJECT

public:
    explicit Task(QWidget *parent = nullptr);
    ~Task();

    QString name() const;
    void setName(const QString& name);
    bool isCompleted() const;

    bool load(const QJsonObject& json);
    void save(QJsonObject& json) const;

signals:
    void removed(Task* task);
    void statusChanged(Task* task);

public slots:
    void rename();
    void checked(bool checked);

private slots:
    void removeSelf();

private:
    Ui::Task *ui;
};

#endif // TASK_H
