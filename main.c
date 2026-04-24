#include <stdio.h>
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

    char* insert_sql = "INSERT INTO student(name,age,major) VALUES('小明',18,'软件工程');";
    int ret=mysql_query(conn,insert_sql);
    if(ret!=0)
    {
        printf("插入失败,error:%s\n",mysql_error(conn));
        mysql_close(conn);
        return 1;
    }
    mysql_query(conn,"COMMIT");
    printf("数据插入成功\n");

    char* select_sql="SELECT id,name,age,major,create_time FROM student;";
    mysql_query(conn,select_sql);

    MYSQL_RES* res=mysql_store_result(conn);
    MYSQL_ROW row;

    printf("id\tname\tage\tmajor\tcreate_time\n");
    
    while((row=mysql_fetch_row(res)))
    {
        printf("%s\t%s\t%s\t%s\t%s\n",row[0],row[1],row[2],row[3],row[4]);
    }

    char* update_sql="UPDATE student SET major='计算机科学' WHERE id=1;";
    mysql_query(conn,update_sql);

    char* delete_sql="DELETE FROM student WHERE id=6;";
    mysql_query(conn,delete_sql);

    select_sql="SELECT id,name,age,major,create_time FROM student;";
    mysql_query(conn,select_sql);

    printf("id\tname\tage\tmajor\tcreate_time\n");

    res=mysql_store_result(conn);
    while((row=mysql_fetch_row(res)))
    {
        printf("%s\t%s\t%s\t%s\t%s\n",row[0],row[1],row[2],row[3],row[4]);
    }

    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}