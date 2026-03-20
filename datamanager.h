#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "student.h"
#include <QVector>
#include <QString>

/**
 * @brief 数据管理类
 * 负责学生数据的增删改查和文件读写
 */
class DataManager
{
public:
    DataManager();

    /**
     * @brief 添加学生
     * @param student 学生对象
     * @return 是否添加成功（学号不重复才成功）
     */
    bool addStudent(const Student &student);

    /**
     * @brief 根据学号删除学生
     * @param id 学号
     * @return 是否删除成功
     */
    bool deleteStudent(QString id);

    /**
     * @brief 更新学生信息
     * @param id 原学号
     * @param updatedStudent 更新后的学生信息
     * @return 是否更新成功
     */
    bool updateStudent(QString id, const Student &updatedStudent);

    /**
     * @brief 根据学号查找学生
     * @param id 学号
     * @return 学生指针，找不到返回nullptr
     */
    Student* findStudentById(QString id);

    /**
     * @brief 根据姓名模糊查找
     * @param name 姓名关键字
     * @return 匹配的学生列表
     */
    QVector<Student> searchStudentsByName(QString name);

    /**
     * @brief 获取所有学生
     * @return 学生列表
     */
    QVector<Student> getAllStudents() const;

    /**
     * @brief 获取学生总数
     * @return 学生数量
     */
    int getStudentCount() const;

    /**
     * @brief 保存数据到文件
     * @param filePath 文件路径
     * @return 是否保存成功
     */
    bool saveToFile(QString filePath);

    /**
     * @brief 从文件加载数据
     * @param filePath 文件路径
     * @return 是否加载成功
     */
    bool loadFromFile(QString filePath);

    /**
     * @brief 清空所有数据
     */
    void clear();

private:
    QVector<Student> m_students;  // 存储所有学生信息
};

#endif // DATAMANAGER_H
