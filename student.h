#ifndef STUDENT_H
#define STUDENT_H

#include <QString>

/**
 * @brief 学生信息类
 * 存储单个学生的基本信息
 */
class Student
{
public:
    Student();
    Student(QString id, QString name, QString gender, int age, QString major, double gpa);

    // Getter方法
    QString getId() const;
    QString getName() const;
    QString getGender() const;
    int getAge() const;
    QString getMajor() const;
    double getGpa() const;

    // Setter方法
    void setId(QString id);
    void setName(QString name);
    void setGender(QString gender);
    void setAge(int age);
    void setMajor(QString major);
    void setGpa(double gpa);

private:
    QString m_id;      // 学号
    QString m_name;    // 姓名
    QString m_gender;  // 性别
    int m_age;         // 年龄
    QString m_major;   // 专业
    double m_gpa;      // 平均学分绩点
};

#endif // STUDENT_H
