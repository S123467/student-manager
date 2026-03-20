#include "datamanager.h"
#include <QFile>
#include <QTextStream>
#include <algorithm>

/**
 * @brief 构造函数
 */
DataManager::DataManager()
{
}

/**
 * @brief 添加学生
 * @param student 学生对象
 * @return 是否添加成功
 */
bool DataManager::addStudent(const Student &student)
{
    // 检查学号是否已存在
    for (const auto &s : m_students) {
        if (s.getId() == student.getId()) {
            return false;  // 学号重复，添加失败
        }
    }
    m_students.append(student);
    return true;
}

/**
 * @brief 根据学号删除学生
 * @param id 学号
 * @return 是否删除成功
 */
bool DataManager::deleteStudent(QString id)
{
    for (int i = 0; i < m_students.size(); i++) {
        if (m_students[i].getId() == id) {
            m_students.remove(i);
            return true;
        }
    }
    return false;
}

/**
 * @brief 更新学生信息
 * @param id 原学号
 * @param updatedStudent 更新后的学生信息
 * @return 是否更新成功
 */
bool DataManager::updateStudent(QString id, const Student &updatedStudent)
{
    for (int i = 0; i < m_students.size(); i++) {
        if (m_students[i].getId() == id) {
            // 如果学号改变了，需要检查新学号是否重复
            if (id != updatedStudent.getId()) {
                for (const auto &s : m_students) {
                    if (s.getId() == updatedStudent.getId() && &s != &m_students[i]) {
                        return false;  // 新学号已存在
                    }
                }
            }
            m_students[i] = updatedStudent;
            return true;
        }
    }
    return false;
}

/**
 * @brief 根据学号查找学生
 * @param id 学号
 * @return 学生指针
 */
Student* DataManager::findStudentById(QString id)
{
    for (int i = 0; i < m_students.size(); i++) {
        if (m_students[i].getId() == id) {
            return &m_students[i];
        }
    }
    return nullptr;
}

/**
 * @brief 根据姓名模糊查找
 * @param name 姓名关键字
 * @return 匹配的学生列表
 */
QVector<Student> DataManager::searchStudentsByName(QString name)
{
    QVector<Student> result;
    for (const auto &student : m_students) {
        if (student.getName().contains(name, Qt::CaseInsensitive)) {
            result.append(student);
        }
    }
    return result;
}

/**
 * @brief 获取所有学生
 * @return 学生列表
 */
QVector<Student> DataManager::getAllStudents() const
{
    return m_students;
}

/**
 * @brief 获取学生总数
 * @return 学生数量
 */
int DataManager::getStudentCount() const
{
    return m_students.size();
}

/**
 * @brief 保存数据到文件（JSON格式，简单实现）
 * @param filePath 文件路径
 * @return 是否保存成功
 */
bool DataManager::saveToFile(QString filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream out(&file);
    // 简单格式：每行一个学生，用逗号分隔各字段
    // 格式：学号,姓名,性别,年龄,专业,绩点
    for (const auto &student : m_students) {
        out << student.getId() << ","
            << student.getName() << ","
            << student.getGender() << ","
            << student.getAge() << ","
            << student.getMajor() << ","
            << student.getGpa() << "\n";
    }

    file.close();
    return true;
}

/**
 * @brief 从文件加载数据
 * @param filePath 文件路径
 * @return 是否加载成功
 */
bool DataManager::loadFromFile(QString filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    clear();
    QTextStream in(&file);
    QString line;
    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList fields = line.split(",");
        if (fields.size() >= 6) {
            Student student(
                fields[0].trimmed(),
                fields[1].trimmed(),
                fields[2].trimmed(),
                fields[3].trimmed().toInt(),
                fields[4].trimmed(),
                fields[5].trimmed().toDouble()
            );
            m_students.append(student);
        }
    }

    file.close();
    return true;
}

/**
 * @brief 清空所有数据
 */
void DataManager::clear()
{
    m_students.clear();
}
