#include "task.h"
#include "ui_task.h"

#include <QInputDialog>
#include <QDebug>
#include <QJsonObject>


Task::Task(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Task)
{
    ui->setupUi(this);
    connect(ui->editButton, &QPushButton::clicked,
            this, &Task::rename);
    connect(ui->checkBox, &QCheckBox::clicked,
            this, &Task::checked);
    //    connect(
    //                ui->removeButton, &QPushButton::clicked,
    //                this, &Task::removeSelf
    //                );
    connect(ui->removeButton, &QPushButton::clicked,
            this, [this](){ this->emit removed(this); });
}

Task::~Task()
{
    qDebug() << "task " << name() << " deleted";
    delete ui;
}

void Task::rename()
{
    bool ok;
    QString value = QInputDialog::getText(
                this, tr("Edit task"),
                tr("Task name"),
                QLineEdit::Normal,
                this->name(), &ok);
    if (ok && !value.isEmpty()) {
        setName(value);
    }
}

void Task::removeSelf()
{
    emit removed(this);
}

void Task::checked(bool checked)
{
    QFont font(ui->checkBox->font());
    font.setStrikeOut(checked);
    ui->checkBox->setFont(font);
    emit statusChanged(this);
}

QString Task::name() const
{
    return ui->checkBox->text();
}

void Task::setName(const QString& name) {
    if (name != this->name()) {
        ui->checkBox->setText(name);
    }
}

bool Task::isCompleted() const {
    return ui->checkBox->isChecked();
}

bool Task::load(const QJsonObject& json)
{
    QString name;
    if (json.contains("name") && json["name"].isString())
    {
        name = json["name"].toString();
    } else {
        return false;
    }

    if (json.contains("checked") && json["checked"].isBool())
    {
        bool checked = json["checked"].toBool();
        this->setName(name);
        this->ui->checkBox->setCheckState(checked ? Qt::Checked : Qt::Unchecked);
        this->checked(checked);
    } else {
        return false;
    }

    return true;
}

void Task::save(QJsonObject& json) const
{
    json["name"] = this->name();
    json["checked"] = this->isCompleted();
}
