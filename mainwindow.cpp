#include "mainwindow.h"
#include <QHeaderView>
#include <QDateTime>

/**
 * @brief 构造函数，创建UI界面
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 设置窗口标题和大小
    setWindowTitle("学生信息管理系统 - 大学生计算机设计大赛");
    setMinimumSize(800, 600);
    resize(900, 650);

    m_defaultFilePath = "students.data";

    // 创建中央部件和主布局
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // === 输入区域 ===
    QGroupBox *inputGroup = new QGroupBox("学生信息录入");
    QGridLayout *inputLayout = new QGridLayout;

    // 学号
    inputLayout->addWidget(new QLabel("学号:"), 0, 0);
    m_idEdit = new QLineEdit;
    m_idEdit->setPlaceholderText("请输入学号（如2024001）");
    inputLayout->addWidget(m_idEdit, 0, 1);

    // 姓名
    inputLayout->addWidget(new QLabel("姓名:"), 0, 2);
    m_nameEdit = new QLineEdit;
    m_nameEdit->setPlaceholderText("请输入姓名");
    inputLayout->addWidget(m_nameEdit, 0, 3);

    // 性别
    inputLayout->addWidget(new QLabel("性别:"), 1, 0);
    m_genderCombo = new QComboBox;
    m_genderCombo->addItem("男");
    m_genderCombo->addItem("女");
    inputLayout->addWidget(m_genderCombo, 1, 1);

    // 年龄
    inputLayout->addWidget(new QLabel("年龄:"), 1, 2);
    m_ageSpin = new QSpinBox;
    m_ageSpin->setRange(14, 30);
    m_ageSpin->setValue(18);
    inputLayout->addWidget(m_ageSpin, 1, 3);

    // 专业
    inputLayout->addWidget(new QLabel("专业:"), 2, 0);
    m_majorEdit = new QLineEdit;
    m_majorEdit->setPlaceholderText("请输入专业名称");
    inputLayout->addWidget(m_majorEdit, 2, 1);

    // GPA
    inputLayout->addWidget(new QLabel("绩点:"), 2, 2);
    m_gpaSpin = new QDoubleSpinBox;
    m_gpaSpin->setRange(0.0, 4.0);
    m_gpaSpin->setSingleStep(0.1);
    m_gpaSpin->setDecimals(2);
    m_gpaSpin->setValue(3.0);
    inputLayout->addWidget(m_gpaSpin, 2, 3);

    inputGroup->setLayout(inputLayout);
    mainLayout->addWidget(inputGroup);

    // === 按钮区域 ===
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    QPushButton *addBtn = new QPushButton("添加");
    QPushButton *deleteBtn = new QPushButton("删除");
    QPushButton *updateBtn = new QPushButton("更新");
    QPushButton *clearBtn = new QPushButton("清空");
    QPushButton *saveBtn = new QPushButton("保存到文件");
    QPushButton *loadBtn = new QPushButton("从文件加载");

    addBtn->setStyleSheet("background-color: #4CAF50; color: white; padding: 8px;");
    deleteBtn->setStyleSheet("background-color: #f44336; color: white; padding: 8px;");
    updateBtn->setStyleSheet("background-color: #2196F3; color: white; padding: 8px;");
    clearBtn->setStyleSheet("padding: 8px;");
    saveBtn->setStyleSheet("padding: 8px;");
    loadBtn->setStyleSheet("padding: 8px;");

    buttonLayout->addWidget(addBtn);
    buttonLayout->addWidget(deleteBtn);
    buttonLayout->addWidget(updateBtn);
    buttonLayout->addWidget(clearBtn);
    buttonLayout->addStretch();
    buttonLayout->addWidget(saveBtn);
    buttonLayout->addWidget(loadBtn);

    mainLayout->addLayout(buttonLayout);

    // === 搜索区域 ===
    QHBoxLayout *searchLayout = new QHBoxLayout;
    searchLayout->addWidget(new QLabel("搜索姓名:"));
    m_searchEdit = new QLineEdit;
    m_searchEdit->setPlaceholderText("输入姓名关键字，点击搜索");
    searchLayout->addWidget(m_searchEdit);
    QPushButton *searchBtn = new QPushButton("搜索");
    QPushButton *showAllBtn = new QPushButton("显示全部");
    searchBtn->setStyleSheet("padding: 6px 16px;");
    showAllBtn->setStyleSheet("padding: 6px 16px;");
    searchLayout->addWidget(searchBtn);
    searchLayout->addWidget(showAllBtn);
    mainLayout->addLayout(searchLayout);

    // === 表格区域 ===
    QGroupBox *tableGroup = new QGroupBox("学生信息列表");
    QVBoxLayout *tableLayout = new QVBoxLayout;

    m_tableWidget = new QTableWidget;
    m_tableWidget->setColumnCount(6);
    m_tableWidget->setHorizontalHeaderLabels(QStringList() << "学号" << "姓名" << "性别" << "年龄" << "专业" << "绩点");
    m_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_tableWidget->verticalHeader()->setVisible(false);
    m_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableWidget->setAlternatingRowColors(true);

    tableLayout->addWidget(m_tableWidget);
    tableGroup->setLayout(tableLayout);
    mainLayout->addWidget(tableGroup);

    // === 连接信号槽 ===
    connect(addBtn, &QPushButton::clicked, this, &MainWindow::onAddStudent);
    connect(deleteBtn, &QPushButton::clicked, this, &MainWindow::onDeleteStudent);
    connect(updateBtn, &QPushButton::clicked, this, &MainWindow::onUpdateStudent);
    connect(clearBtn, &QPushButton::clicked, this, &MainWindow::onClearInput);
    connect(saveBtn, &QPushButton::clicked, this, &MainWindow::onSaveToFile);
    connect(loadBtn, &QPushButton::clicked, this, &MainWindow::onLoadFromFile);
    connect(searchBtn, &QPushButton::clicked, this, &MainWindow::onSearchStudent);
    connect(showAllBtn, &QPushButton::clicked, this, &MainWindow::onShowAll);
    connect(m_tableWidget, &QTableWidget::cellClicked, this, &MainWindow::onTableClicked);

    // 尝试加载默认数据文件
    if (QFile::exists(m_defaultFilePath)) {
        m_dataManager.loadFromFile(m_defaultFilePath);
    }

    // 刷新表格
    refreshTable();
}

/**
 * @brief 析构函数
 */
MainWindow::~MainWindow()
{
}

/**
 * @brief 添加新学生
 */
void MainWindow::onAddStudent()
{
    QString id = m_idEdit->text().trimmed();
    QString name = m_nameEdit->text().trimmed();
    QString gender = m_genderCombo->currentText();
    int age = m_ageSpin->value();
    QString major = m_majorEdit->text().trimmed();
    double gpa = m_gpaSpin->value();

    // 输入验证
    if (id.isEmpty() || name.isEmpty() || major.isEmpty()) {
        showMessage("请填写完整的学生信息！", true);
        return;
    }

    Student student(id, name, gender, age, major, gpa);
    bool success = m_dataManager.addStudent(student);

    if (success) {
        refreshTable();
        onClearInput();
        showMessage(QString("成功添加学生：%1").arg(name));
    } else {
        showMessage(QString("添加失败，学号 %1 已存在！").arg(id), true);
    }
}

/**
 * @brief 删除选中的学生
 */
void MainWindow::onDeleteStudent()
{
    int selectedRow = m_tableWidget->currentRow();
    if (selectedRow < 0) {
        showMessage("请先选择要删除的学生！", true);
        return;
    }

    QString id = m_tableWidget->item(selectedRow, 0)->text();
    QString name = m_tableWidget->item(selectedRow, 1)->text();

    QMessageBox::StandardButton confirm = QMessageBox::question(
        this, "确认删除",
        QString("确定要删除学生 %1 (%2) 吗？").arg(name, id),
        QMessageBox::Yes | QMessageBox::No
    );

    if (confirm == QMessageBox::Yes) {
        bool success = m_dataManager.deleteStudent(id);
        if (success) {
            refreshTable();
            onClearInput();
            showMessage(QString("成功删除学生：%1").arg(name));
        } else {
            showMessage("删除失败！", true);
        }
    }
}

/**
 * @brief 更新学生信息
 */
void MainWindow::onUpdateStudent()
{
    int selectedRow = m_tableWidget->currentRow();
    if (selectedRow < 0) {
        showMessage("请先选择要更新的学生！点击表格行选择", true);
        return;
    }

    QString oldId = m_tableWidget->item(selectedRow, 0)->text();
    QString id = m_idEdit->text().trimmed();
    QString name = m_nameEdit->text().trimmed();
    QString gender = m_genderCombo->currentText();
    int age = m_ageSpin->value();
    QString major = m_majorEdit->text().trimmed();
    double gpa = m_gpaSpin->value();

    if (id.isEmpty() || name.isEmpty() || major.isEmpty()) {
        showMessage("请填写完整的学生信息！", true);
        return;
    }

    Student student(id, name, gender, age, major, gpa);
    bool success = m_dataManager.updateStudent(oldId, student);

    if (success) {
        refreshTable();
        onClearInput();
        showMessage(QString("成功更新学生信息：%1").arg(name));
    } else {
        showMessage("更新失败！新学号已存在或找不到原记录。", true);
    }
}

/**
 * @brief 搜索学生
 */
void MainWindow::onSearchStudent()
{
    QString keyword = m_searchEdit->text().trimmed();
    if (keyword.isEmpty()) {
        onShowAll();
        return;
    }

    QVector<Student> results = m_dataManager.searchStudentsByName(keyword);
    refreshTable(results);
    showMessage(QString("找到 %1 条匹配记录").arg(results.size()));
}

/**
 * @brief 显示所有学生
 */
void MainWindow::onShowAll()
{
    m_searchEdit->clear();
    refreshTable();
    showMessage(QString("共显示 %1 条记录").arg(m_dataManager.getStudentCount()));
}

/**
 * @brief 保存数据到文件
 */
void MainWindow::onSaveToFile()
{
    QString filePath = QFileDialog::getSaveFileName(
        this, "保存数据文件",
        m_defaultFilePath,
        "数据文件 (*.data *.txt);;所有文件 (*)"
    );

    if (filePath.isEmpty()) {
        return;
    }

    bool success = m_dataManager.saveToFile(filePath);
    if (success) {
        m_defaultFilePath = filePath;
        showMessage(QString("数据已保存到：%1").arg(filePath));
    } else {
        showMessage("保存失败！无法写入文件。", true);
    }
}

/**
 * @brief 从文件加载数据
 */
void MainWindow::onLoadFromFile()
{
    QString filePath = QFileDialog::getOpenFileName(
        this, "加载数据文件",
        ".",
        "数据文件 (*.data *.txt);;所有文件 (*)"
    );

    if (filePath.isEmpty()) {
        return;
    }

    bool success = m_dataManager.loadFromFile(filePath);
    if (success) {
        m_defaultFilePath = filePath;
        refreshTable();
        showMessage(QString("成功加载 %1 条记录").arg(m_dataManager.getStudentCount()));
    } else {
        showMessage("加载失败！无法读取文件。", true);
    }
}

/**
 * @brief 清空输入框
 */
void MainWindow::onClearInput()
{
    m_idEdit->clear();
    m_nameEdit->clear();
    m_majorEdit->clear();
    m_genderCombo->setCurrentIndex(0);
    m_ageSpin->setValue(18);
    m_gpaSpin->setValue(3.0);
    m_tableWidget->clearSelection();
}

/**
 * @brief 表格点击事件，填充输入框
 */
void MainWindow::onTableClicked(int row)
{
    if (row < 0) return;

    QString id = m_tableWidget->item(row, 0)->text();
    QString name = m_tableWidget->item(row, 1)->text();
    QString gender = m_tableWidget->item(row, 2)->text();
    int age = m_tableWidget->item(row, 3)->text().toInt();
    QString major = m_tableWidget->item(row, 4)->text();
    double gpa = m_tableWidget->item(row, 5)->text().toDouble();

    m_idEdit->setText(id);
    m_nameEdit->setText(name);
    m_genderCombo->setCurrentText(gender);
    m_ageSpin->setValue(age);
    m_majorEdit->setText(major);
    m_gpaSpin->setValue(gpa);
}

/**
 * @brief 刷新表格显示（全部）
 */
void MainWindow::refreshTable()
{
    refreshTable(m_dataManager.getAllStudents());
}

/**
 * @brief 刷新表格显示（指定列表）
 */
void MainWindow::refreshTable(const QVector<Student> &students)
{
    m_tableWidget->setRowCount(students.size());

    for (int i = 0; i < students.size(); i++) {
        const Student &s = students[i];
        m_tableWidget->setItem(i, 0, new QTableWidgetItem(s.getId()));
        m_tableWidget->setItem(i, 1, new QTableWidgetItem(s.getName()));
        m_tableWidget->setItem(i, 2, new QTableWidgetItem(s.getGender()));
        m_tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(s.getAge())));
        m_tableWidget->setItem(i, 4, new QTableWidgetItem(s.getMajor()));
        m_tableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(s.getGpa(), 'f', 2)));
    }
}

/**
 * @brief 显示提示信息到状态栏
 */
void MainWindow::showMessage(QString message, bool isError)
{
    statusBar()->showMessage(message, 3000);

    if (isError) {
        QMessageBox::warning(this, "提示", message);
    }
}
