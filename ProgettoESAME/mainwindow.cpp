#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    caricaDaFile();

    connect(ui->calendarWidget, &QCalendarWidget::clicked,
            this, &MainWindow::onDateClicked);
    connect(ui->checkEndTime, &QCheckBox::toggled,
            ui->timeEnd, &QTimeEdit::setEnabled);
    connect(ui->btnSaveTask, &QPushButton::clicked,
            this, &MainWindow::onSaveTaskClicked);
    connect(ui->btnUpdateTask, &QPushButton::clicked,
            this, &MainWindow::onUpdateTaskClicked);
    connect(ui->btnDeleteTask, &QPushButton::clicked,
            this, &MainWindow::onDeleteTaskClicked);
    connect(ui->tableActivities, &QTableWidget::itemSelectionChanged,
            this, &MainWindow::onTableSelectionChanged);
    connect(ui->tableActivities, &QTableWidget::itemClicked,
            this, &MainWindow::onTableItemClicked);


    selectedDate = QDate::currentDate();
    ui->calendarWidget->setSelectedDate(selectedDate);
    refreshTable(selectedDate);
}

MainWindow::~MainWindow()
{
    salvaSuFile();
    delete ui;
}

void MainWindow::onDateClicked(const QDate &date){
    selectedDate = date;
    refreshTable(selectedDate);
}

void MainWindow::refreshTable(const QDate &date){

    ui->tableActivities->setRowCount(0);
    QList<Task> tasksOfDay = tasksByDate.value(date);

    // ordinamento per ora di inizio attività
    for(int i = 0; i < tasksOfDay.size()-1; ++i){
        for(int j = i+1; j < tasksOfDay.size(); ++j){

            if(tasksOfDay[j].startTime < tasksOfDay[i].startTime){
                Task temp = tasksOfDay[i];
                tasksOfDay[i] = tasksOfDay[j];
                tasksOfDay[j] = temp;
            }
        }
    }

    for(int i = 0; i < tasksOfDay.size(); ++i){
        int row = ui->tableActivities->rowCount();
        ui->tableActivities->insertRow(row);

        QString typeText;
        if(tasksOfDay[i].type == TaskType::Event){
            typeText = "Evento";
        }else{
            typeText = "Attività";
        }
        ui->tableActivities->setItem(row, 0, new QTableWidgetItem(typeText));
        ui->tableActivities->setItem(row, 1, new QTableWidgetItem(tasksOfDay[i].title));
        ui->tableActivities->setItem(row, 2, new QTableWidgetItem(tasksOfDay[i].startTime.toString("HH:mm")));
        if(tasksOfDay[i].hasEndTime){
             ui->tableActivities->setItem(row, 3, new QTableWidgetItem(tasksOfDay[i].endTime.toString("HH:mm")));
        } else {
             ui->tableActivities->setItem(row, 3, new QTableWidgetItem("-"));
        }
        ui->tableActivities->setItem(row, 4, new QTableWidgetItem(tasksOfDay[i].frequency));

    }

}

void MainWindow::onSaveTaskClicked(){

    QTime oraInizio = ui->timeStart->time();
    QTime oraFine;

    if(ui->checkEndTime->isChecked()){
        oraFine = ui->timeEnd->time();
    }else{
        oraFine = oraInizio;
    }

    if(esisteSovrapposizione(selectedDate, oraInizio, oraFine)){
        QMessageBox::warning(this, "Sovrapposizione evento", "Esiste già un'attività in questa fascia oraria.");
        return;
    }


    Task task;

    if(ui->comboType->currentText()=="Evento"){
        task.type = TaskType::Event;
    }else{
        task.type = TaskType::Activity;
    }

    task.title = ui->editTitle->text();
    task.startTime = ui->timeStart->time();

    task.hasEndTime = ui->checkEndTime->isChecked();
    if(task.hasEndTime){
        task.endTime = ui->timeEnd->time();
    }

    task.frequency = ui->comboFrequency->currentText();
    task.completed = false;

    tasksByDate[selectedDate].append(task);
    salvaSuFile();
    refreshTable(selectedDate);

}

void MainWindow::onUpdateTaskClicked(){

    if(index_task_da_editare < 0)
        return;

    QList<Task> &tasksOfDay = tasksByDate[selectedDate];

    if(index_task_da_editare >= tasksOfDay.size())
        return;

    Task &task = tasksOfDay[index_task_da_editare];

    if(ui->comboType->currentText()=="Evento"){
        task.type = TaskType::Event;
    }else{
        task.type = TaskType::Activity;
    }

    task.title = ui->editTitle->text();
    task.startTime = ui->timeStart->time();

    task.hasEndTime = ui->checkEndTime->isChecked();
    if(task.hasEndTime){
        task.endTime = ui->timeEnd->time();
    }

    task.frequency = ui->comboFrequency->currentText();

    index_task_da_editare = -1;

    salvaSuFile();

    refreshTable(selectedDate);

}

void MainWindow::onTableSelectionChanged(){

    bool selection = !ui->tableActivities->selectedItems().isEmpty();
    ui->btnDeleteTask->setEnabled(selection);
    ui->btnUpdateTask->setEnabled(selection);
}

void MainWindow::onDeleteTaskClicked(){

    int row = ui->tableActivities->currentRow();

    // Nessuna riga selezionata
    if(row < 0)
        return;

    // recupero la lista di attività del giorno
    QList<Task> &tasksOfDay = tasksByDate[selectedDate];

    // controllo di sicurezza
    if(row >= tasksOfDay.size())
        return;

    // rimuovo l'attività
    tasksOfDay.removeAt(row);

    salvaSuFile();

    refreshTable(selectedDate);
}

void MainWindow::onTableItemClicked(QTableWidgetItem *item){

    int row = item->row();
    QList<Task> &tasksOfDay = tasksByDate[selectedDate];

    if(row < 0 || row >= tasksOfDay.size())
        return;

    const Task &task = tasksOfDay[row];
    index_task_da_editare = row;

    ui->comboType->setCurrentText(task.type == TaskType::Event ? "Evento" : "Attività");
    ui->editTitle->setText(task.title);
    ui->timeStart->setTime(task.startTime);
    ui->checkEndTime->setChecked(task.hasEndTime);
    ui->timeEnd->setEnabled(task.hasEndTime);
    if(task.hasEndTime)
        ui->timeEnd->setTime(task.endTime);

    ui->comboFrequency->setCurrentText(task.frequency);
}

bool MainWindow::esisteSovrapposizione(const QDate &date, const QTime &start, const QTime &end){

    const QList<Task> &tasksOfDay = tasksByDate.value(date);

    for(int i = 0; i < tasksOfDay.size(); ++i){

        QTime otherStart = tasksOfDay[i].startTime;
        QTime otherEnd;

        if(tasksOfDay[i].hasEndTime){
            otherEnd = tasksOfDay[i].endTime;
        }else{
            otherEnd = tasksOfDay[i].startTime;
        }

        if((start < otherEnd) && (end > otherStart)){
            return true;
        }
    }

    return false;
}

// attività su file

void MainWindow::salvaSuFile(){

    QFile file("attivita.txt");

    // apro file in scrittura, se non esiste lo crea
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);

    QList<QDate> date = tasksByDate.keys();

    for(int i = 0; i < date.size(); ++i){

        QList<Task> lista = tasksByDate[date[i]];

        for(int j = 0; j < lista.size(); ++j){

            out << date[i].toString("yyyy-MM-dd") << ";"
                << (lista[j].type == TaskType::Event ? "Evento" : "Attività") << ";"
                << lista[j].title << ";"
                << lista[j].startTime.toString("HH:mm") << ";";

            if(lista[j].hasEndTime)
                out << lista[j].endTime.toString("HH:mm");
            else
                out << "";

            out << ";" <<lista[j].frequency << ";"
                << (lista[j].completed ? "1":"0") <<"\n";
        }
    }

    file.close();
    qDebug() << "File salvato in: " << QFileInfo(file).absoluteFilePath();
}

void MainWindow::caricaDaFile(){

    QFile file("attivita.txt");

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);

    while(!in.atEnd()){
        QString riga = in.readLine();
        QStringList parti = riga.split(";");

        QDate data = QDate::fromString(parti[0], "yyyy-MM-dd");

        Task t;

        t.type = (parti[1] == "Evento") ? TaskType::Event : TaskType::Activity;
        t.title = parti[2];
        t.startTime = QTime::fromString(parti[3], "HH:mm");
        if(!parti[4].isEmpty()){
            t.endTime = QTime::fromString(parti[4], "HH:mm");
            t.hasEndTime = true;
        }else{
            t.hasEndTime = false;
        }

        t.frequency = parti[5];

        tasksByDate[data].append(t);
    }

    file.close();






}









