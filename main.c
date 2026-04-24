#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main()
{
    MYSQL * conn=mysql_init(NULL);
    if(conn==NULL)
    {
        printf("初始化失败\n");
        return 1;
    }

    conn = mysql_real_connect(
        conn,
        "localhost",
        "root",
        "123456",
        "myproject",
        3306,
        NULL,
        0
    );

    if(conn==NULL)
    {
        printf("数据库连接失败\n");
        return 1;
    }

    printf("连接成功\n");

    const char* insert_sql = "INSERT INTO student(name,age,major) VALUES('小明',18,'软件工程');";
    int ret=mysql_query(conn,insert_sql);
    if(ret!=0)
    {
        printf("插入失败,error:%s\n",mysql_error(conn));
        mysql_close(conn);
        return 1;
    }
    
    printf("数据插入成功\n");

    const char* select_sql="SELECT id,name,age,major,create_time FROM student;";
    mysql_query(conn,select_sql);

    MYSQL_RES* res=mysql_store_result(conn);
    MYSQL_ROW row;

    printf("id\tname\tage\tmajor\tcreate_time\n");
    
    while((row=mysql_fetch_row(res)))
    {
        printf("%s\t%s\t%s\t%s\t%s\n",row[0],row[1],row[2],row[3],row[4]);
    }
    mysql_free_result(res);

    const char* update_sql="UPDATE student SET major='计算机科学' WHERE id=1;";
    if(mysql_query(conn,update_sql)!=0)
    {
        printf("修改失败：%s\n",mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    const char* delete_sql="DELETE FROM student WHERE id=6;";
    if(mysql_query(conn,delete_sql)!=0)
    {
        printf("删除失败：%s\n",mysql_error(conn));
        mysql_close(conn);
        return 1;
    }
    //mysql_query(conn,"COMMIT");

    mysql_query(conn,select_sql);
    res=mysql_store_result(conn);

    printf("id\tname\tage\tmajor\tcreate_time\n");

    while((row=mysql_fetch_row(res)))
    {
        printf("%s\t%s\t%s\t%s\t%s\n",row[0],row[1],row[2],row[3],row[4]);
    }
    mysql_free_result(res);

    const char* select_sql1="SELECT id,name,age,major,create_time FROM student WHERE age>18;";
    if(mysql_query(conn,select_sql1)!=0)
    {
        printf("查找失败：%s\n",mysql_error(conn));
        mysql_close(conn);
        return 1;
    }
    res=mysql_store_result(conn);
    printf("id\tname\tage\tmajor\tcreate_time\n");
    while((row=mysql_fetch_row(res)))
    {
        printf("%s\t%s\t%s\t%s\t%s\n",row[0],row[1],row[2],row[3],row[4]);
    }
    mysql_free_result(res);

    const char* select_sql2="SELECT id,name,age,major,create_time FROM student ORDER BY id DESC;";
    if(mysql_query(conn,select_sql2)!=0)
    {
        printf("排序查找失败：%s\n",mysql_error(conn));
        mysql_close(conn);
        return 1;
    }
    res=mysql_store_result(conn);
    printf("id\tname\tage\tmajor\tcreate_time\n");
    while((row=mysql_fetch_row(res)))
    {
        printf("%s\t%s\t%s\t%s\t%s\n",row[0],row[1],row[2],row[3],row[4]);
    }
    mysql_free_result(res);

    const char* select_sql3="SELECT id,name,age,major,create_time FROM student WHERE major LIKE '%计算机%';";
    if(mysql_query(conn,select_sql3)!=0)
    {
        printf("模糊查找失败：%s\n",mysql_error(conn));
        mysql_close(conn);
        return 1;
    }
    res=mysql_store_result(conn);
    printf("id\tname\tage\tmajor\tcreate_time\n");
    while((row=mysql_fetch_row(res)))
    {
        printf("%s\t%s\t%s\t%s\t%s\n",row[0],row[1],row[2],row[3],row[4]);
    }

    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}