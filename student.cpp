#include "student.h"

/**
 * @brief 默认构造函数
 */
Student::Student()
    : m_id("")
    , m_name("")
    , m_gender("男")
    , m_age(18)
    , m_major("")
    , m_gpa(0.0)
{
}

/**
 * @brief 带参数的构造函数
 * @param id 学号
 * @param name 姓名
 * @param gender 性别
 * @param age 年龄
 * @param major 专业
 * @param gpa 平均学分绩点
 */
Student::Student(QString id, QString name, QString gender, int age, QString major, double gpa)
    : m_id(id)
    , m_name(name)
    , m_gender(gender)
    , m_age(age)
    , m_major(major)
    , m_gpa(gpa)
{
}

// Getter方法实现
QString Student::getId() const { return m_id; }
QString Student::getName() const { return m_name; }
QString Student::getGender() const { return m_gender; }
int Student::getAge() const { return m_age; }
QString Student::getMajor() const { return m_major; }
double Student::getGpa() const { return m_gpa; }

// Setter方法实现
void Student::setId(QString id) { m_id = id; }
void Student::setName(QString name) { m_name = name; }
void Student::setGender(QString gender) { m_gender = gender; }
void Student::setAge(int age) { m_age = age; }
void Student::setMajor(QString major) { m_major = major; }
void Student::setGpa(double gpa) { m_gpa = gpa; }
