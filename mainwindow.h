#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QMessageBox>
#include <QFileDialog>
#include <QStatusBar>
#include "datamanager.h"

/**
 * @brief 主窗口类
 * 包含所有GUI界面元素和交互逻辑
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /**
     * @brief 添加新学生
     */
    void onAddStudent();

    /**
     * @brief 删除选中的学生
     */
    void onDeleteStudent();

    /**
     * @brief 更新选中的学生信息
     */
    void onUpdateStudent();

    /**
     * @brief 搜索学生
     */
    void onSearchStudent();

    /**
     * @brief 显示所有学生
     */
    void onShowAll();

    /**
     * @brief 保存数据到文件
     */
    void onSaveToFile();

    /**
     * @brief 从文件加载数据
     */
    void onLoadFromFile();

    /**
     * @brief 清空输入框
     */
    void onClearInput();

    /**
     * @brief 表格点击事件，填充输入框
     */
    void onTableClicked(int row);

private:
    /**
     * @brief 刷新表格显示（全部）
     */
    void refreshTable();

    /**
     * @brief 刷新表格显示（指定列表）
     */
    void refreshTable(const QVector<Student> &students);

    /**
     * @brief 显示提示信息
     */
    void showMessage(QString message, bool isError = false);

    // 数据管理对象
    DataManager m_dataManager;

    // UI组件
    QTableWidget *m_tableWidget;        // 学生信息表格

    // 输入框
    QLineEdit *m_idEdit;                // 学号输入
    QLineEdit *m_nameEdit;              // 姓名输入
    QComboBox *m_genderCombo;           // 性别选择
    QSpinBox *m_ageSpin;                // 年龄输入
    QLineEdit *m_majorEdit;             // 专业输入
    QDoubleSpinBox *m_gpaSpin;          // GPA输入
    QLineEdit *m_searchEdit;            // 搜索输入

    // 默认数据文件路径
    QString m_defaultFilePath;
};

#endif // MAINWINDOW_H
