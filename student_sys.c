#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define USER "root"
#define PASSWORD "123456"
#define DB "myproject"

MYSQL* conn;
MYSQL_RES* res;
MYSQL_ROW row;

void init_mysql()
{
    conn=mysql_init(NULL);
    conn=mysql_real_connect(conn,"localhost",USER,PASSWORD,DB,3306,NULL,0);//全部
    if(conn==NULL)
    {
        printf("连接失败\n");
        exit(1);
    }
    printf("连接成功\n");
}

void close_mysql()
{
    mysql_close(conn);
}

void show_menu()
{
    printf("=====学生管理系统=====\n");
    printf("1.增加学生\n");
    printf("2.删除学生\n");
    printf("3.更改学生\n");
    printf("4.查询学生\n");
    printf("0.退出系统\n");
    printf("请选择：");
}

void stu_add()
{
    char name[20],major[30];
    int age;
    printf("请输入姓名 年龄 专业：");
    scanf("%s %d %s",name,&age,major);
    char sql[256];
    sprintf(sql,"INSERT INTO student(name,age,major) VALUES('%s',%d,'%s');",name,age,major);
    if(mysql_query(conn,sql))
    {
        printf("添加失败:%s\n",mysql_error(conn));
        return;
    }
    printf("添加成功\n");
}

void stu_del()
{
    int id;
    printf("输入删除id:");
    scanf("%d",&id);
    char sql[256];
    sprintf(sql,"DELETE FROM student WHERE id=%d;",id);
    if(mysql_query(conn,sql))
    {
        printf("删除失败：%s\n",mysql_error(conn));
        return;
    }
    printf("删除成功\n");
}

void stu_modify()
{
    int id;
    char new_major[30];
    printf("输入修改id和新专业:");
    scanf("%d %s",&id,new_major);
    char sql[256];
    sprintf(sql,"UPDATE student SET major='%s'WHERE id=%d;",new_major,id);
    if(mysql_query(conn,sql))
    {
        printf("修改失败:%s\n",mysql_error(conn));
        return;
    }
    printf("修改成功\n");
}

void stu_select()
{
    char sql[256]="SELECT id,name,major,create_time FROM student;";
    if(mysql_query(conn,sql))
    {
        printf("查询失败:%s\n",mysql_error(conn));
        return;
    }
    res=mysql_store_result(conn);
    printf("\nid\tname\tage\tmajor\ttime\n");
    while((row=mysql_fetch_row(res)))
    {
        printf("%s\t%s\t%s\t%s\t%s\n",row[0],row[1],row[2],row[3],row[4]);
    }
    mysql_free_result(res);
}

int main()
{
    init_mysql();
    int opt;
    while(1)
    {
        show_menu();
        scanf("%d",&opt);
        switch(opt)
        {
            case 1: stu_add(); break;
            case 2: stu_del(); break;
            case 3: stu_modify(); break;
            case 4: stu_select(); break;
            case 0: close_mysql();
            printf("系统退出\n");
            return 0;
            default: printf("不合理 -_-"); break;
        }
        system("cls");
    }
}