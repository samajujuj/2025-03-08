#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#pragma warning(disable:6031)
#pragma warning(disable:6062)

#define MANGER_PASSWORD 123

#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <time.h>

int instances_user_count();
int instances_book_count();
int censor();
void show_all_book(int ena_user);
void show_myself(int ena_user);
void show_matched_book(int ena_user);
int is_manager(int ena_user, int input_count);
int manager_system(int ena_user);
void book_date_change(int ena_user,int pos, int b_numb, char b_name[], char b_type[], char more_info[], char auther[], char publisling[],int b_state);
void user_date_change(int ena_user,int pos, int u_account, int u_password, int grade, char u_name_input[], char borrowed[]);
void sentry_add(int ena_user,int user_or_book);
void save_books();
void load_books();
void save_users();
void load_users();
void reset_books_to_default();
void reset_users_to_default();
void log_message(const char* action, const char* details);

struct Books {
    int b_numb;
    char b_name[30];
    char b_type[20];
    char b_state[10];
    char auther[50];
    char publishing[50];
    char more_info[500];
};

struct Users {
    int u_account;
    int u_password;
    char u_name[10];
    int grade;
    char borrowed[300];
};

struct Books book_list[10000] = {
    {1001, "C Programming", "Education", "available", "Brian Kernighan", "Prentice Hall", "A fundamental book on C language."},
    {1002, "The Great Gatsby", "Fiction", "borrowed", "F. Scott Fitzgerald", "Scribner", "A classic novel set in the 1920s."},
    {1003, "Data Structures & Algorithms", "Education", "available", "Robert Lafore", "SAMS Publishing", "Comprehensive guide on algorithms."},
    {1004, "1984", "Dystopian", "available", "George Orwell", "Secker & Warburg", "A novel about totalitarian surveillance."},
    {5, "To Kill a Mockingbird", "Fiction", "available", "Harper Lee", "J.B. Lippincott & Co.", "A novel about racial injustice in America."},
    {1006, "Introduction to Algorithms", "Education", "borrowed", "Cormen et al.", "MIT Press", "A widely used textbook on algorithms."},
    {1007, "The Catcher in the Rye", "Fiction", "available", "J.D. Salinger", "Little, Brown and Company", "A novel about teenage angst."},
    {1008, "Brave New World", "Dystopian", "available", "Aldous Huxley", "Chatto & Windus", "A dystopian novel about a future society."},
    {1009, "Artificial Intelligence", "Education", "borrowed", "Stuart Russell", "Pearson", "An introduction to AI concepts."},
    {1010, "The Hobbit", "Fantasy", "available", "J.R.R. Tolkien", "George Allen & Unwin", "A fantasy novel about Bilbo Baggins' journey."},
    {-1, "", "", "", "", "", ""}
};

struct Users user_list[500] = {
    {1, 1, "jujuj", 5,"",},
    {2, 2, "mmcy", 2,"",},
    {103, 9876, "Charlie", 3,"",},
    {104, 5432, "David", 4,"",},
    {105, 6789, "Eve", 5,"",},
    {106, 1122, "Frank", 2,"",},
    {107, 3344, "Grace", 3,"",},
    {108, 5566, "Hannah", 4,"",},
    {109, 7788, "Ivan", 5,"",},
    {110, 9900, "Jack", 1,"",},
    {-1, 0, "", 0,"",}
};

int instances_user_count() 
{
    int count = 0;
    while (user_list[count].u_account != -1) {
        count++;
    }
    return count;
}

int instances_book_count() 
{
    int count = 0;
    while (book_list[count].b_numb != -1) {
        count++;
    }
    return count;
}

int censor() {
    int user_count = instances_user_count(user_list);
    int account_input = 0;
    int password_input = 0;
    int ena_index = 0;
    while (1) {
        printf("你正在试图进入xx借阅系统，请先认证你的身份\n(输入0以退出借阅系统)\n账号：\n");
        scanf("%d", &account_input);
        if (account_input == 0)
        {
            return -1;
        }
        printf("密码：\n");
        scanf("%d", &password_input);
        for (int i = 0; i < user_count; i++) {
            if (account_input == user_list[i].u_account && password_input == user_list[i].u_password) {
                ena_index = i;
                printf("欢迎，%s\n即将进入系统\n", user_list[ena_index].u_name);
                return ena_index;
            }
        }
        printf("\n账户或密码错误\n");
    }
}

void show_all_book(int ena_user) {
    int book_count = instances_book_count();
    int currt_page = 1;
    int total_page = (book_count + 4) / 5;

    while (1) {
        for (int i = (currt_page - 1) * 5; i < currt_page * 5 && i < book_count; i++) {
            printf("\n=====第%d/%d本 图书信息 ========\n", i + 1, book_count);
            printf("书名：%s\n", book_list[i].b_name);
            printf("作者：%s\n", book_list[i].auther);
            printf("出版社：%s\n", book_list[i].publishing);
            printf("编号：%d\n", book_list[i].b_numb);
            printf("类型：%s\n", book_list[i].b_type);
            printf("状态：%s\n", book_list[i].b_state);
            printf("================================\n\n");
        }

        printf("=========== 选项 =========\n");
        printf("当前第 %d/%d 页\n", currt_page, total_page);
        if (currt_page < total_page) {
            printf("1. 下一页\n");
        }
        if (currt_page > 1) {
            printf("2. 上一页\n");
        }
        printf("0. 返回主界面\n");
        printf("或输入书籍编号表示借阅\n");
        printf("==========================\n");

        int s_a_b_input;
        scanf("%d", &s_a_b_input);
        switch (s_a_b_input) {
        case 1:
            if (currt_page < total_page) currt_page++;
            break;
        case 2:
            if (currt_page > 1) currt_page--;
            break;
        case 0:
            return;
        default:
            for (int i = 0; i < book_count; i++) {
                if (s_a_b_input == book_list[i].b_numb) {
                    if (strcmp(book_list[i].b_state, "available") == 0)
                    {
                        char temp[50];
                        sprintf(temp, " %d", book_list[i].b_numb);
                        strcpy(book_list[i].b_state, "borrowed");
                        printf("\n成功借出书籍，名为 %s ，此书现为 %s 状态\n", book_list[i].b_name, book_list[i].b_state);
                        if (strlen(user_list[ena_user].borrowed) == 0)
                        {
                            strcpy((user_list[ena_user].borrowed), book_list[i].b_name);
                            strcat((user_list[ena_user].borrowed), temp);
                        }
                        else {
                            strcat((user_list[ena_user].borrowed), "\n");
                            strcat((user_list[ena_user].borrowed), book_list[i].b_name);
                            strcat((user_list[ena_user].borrowed), temp);
                        }
                    }
                    else if (strcmp(book_list[i].b_state, "borrowed") == 0)
                    {
                        printf("\n名为 %s 书籍借出失败，此书现为 %s 状态\n", book_list[i].b_name, book_list[i].b_state);
                    }
                    Sleep(1000);
                    break;
                }
            }
            break;
        }
    }
}

void show_myself(int ena_user)
{
    int s_m_state = 1;
    int s_m_input;
    int user_index = ena_user;
    int book_count = instances_book_count();
    while (s_m_state)
    {
        printf("\n================我的信息================\n");
        printf("姓名: %s\n", user_list[user_index].u_name);
        printf("编号: %d\n", user_list[user_index].u_account);
        printf("等级: %d\n", user_list[user_index].grade);
        printf("已/曾借阅图书: %s\n", user_list[user_index].borrowed);
        printf("\n========================================\n");

        printf("=========== 选项 =========\n");
        printf("输入编号以完成还书\n");
        printf("0.返回主页面\n");
        printf("==========================\n");
        scanf("%d", &s_m_input);
        char temp[300];
        int found = 0;
        if (s_m_input == 0)
        {
            s_m_state = 0;
        }
        for (int i = 0; i < book_count; i++)
        {
            if (s_m_input == book_list[i].b_numb)
            {
                found = 1;
                if (strstr(user_list[user_index].borrowed, book_list[i].b_name))
                {
                    strcpy(temp, user_list[user_index].borrowed);
                    char* pos = strstr(temp, book_list[i].b_name);
                    if (pos)
                    {
                        size_t len = strlen(book_list[i].b_name);
                        memmove(pos, pos + len, strlen(pos + len) + 1);
                        if (*temp == '\n')
                        {
                            memmove(temp, temp + 1, strlen(temp));
                        }
                        strcpy(user_list[user_index].borrowed, temp);
                    }
                    strcpy(book_list[i].b_state, "available");
                    printf("\n归还书籍 %s 成功\n", book_list[i].b_name);
                    Sleep(1000);
                }
                else
                {
                    printf("\n你尚未借阅 %s \n", book_list[i].b_name);
                }
            }
        }
        if (found == 0 && s_m_input != 0)
        {
            printf("\n未在系统中找到编号为 %d 书籍\n", s_m_input);
        }
    }
}

void show_matched_book(int ena_user)
{
    int book_count = instances_book_count();
    char research[30];
    int matched_count = 0;
    int matched_list[50];
    int research_state = 1;

    printf("\n====== 欢迎进入xx系统查寻部分 ========\n");
    printf("输入书籍关键字以查询：\n");
    printf("0.退出查询\n");
    printf("========================================\n\n");
    scanf("%s", research);
    for (int i = 0; i < book_count; i++)
    {
        if (research[0] == '0')
        {
            return;
        }
        if (strstr(book_list[i].b_name, research))
        {
            matched_list[matched_count] = i;
            matched_count++;
        }
    }
    if (matched_count == 0)
    {
        printf("\n系统中没有符合条件的书籍\n");
        research_state = 0;
    }
    int currt_page = 1;
    int total_page = (matched_count + 4) / 5;
    while (research_state) {
        for (int i = (currt_page - 1) * 5; i < currt_page * 5 && i < matched_count; i++) {
            printf("\n=====第%d/%d本 图书信息 ========\n", i + 1, matched_count);
            printf("书名：%s\n", book_list[matched_list[i]].b_name);
            printf("作者：%s\n", book_list[matched_list[i]].auther);
            printf("出版社：%s\n", book_list[matched_list[i]].publishing);
            printf("编号：%d\n", book_list[matched_list[i]].b_numb);
            printf("类型：%s\n", book_list[matched_list[i]].b_type);
            printf("状态：%s\n", book_list[matched_list[i]].b_state);
            printf("================================\n\n");
        }

        printf("=========== 选项 =========\n");
        printf("当前第 %d/%d 页\n", currt_page, total_page);
        if (currt_page < total_page) {
            printf("1. 下一页\n");
        }
        if (currt_page > 1) {
            printf("2. 上一页\n");
        }
        printf("0. 返回主界面\n");
        printf("或输入书籍编号表示借阅\n");
        printf("==========================\n");

        int s_a_b_input;
        scanf("%d", &s_a_b_input);
        switch (s_a_b_input) {
        case 1:
            if (currt_page < total_page) currt_page++;
            break;
        case 2:
            if (currt_page > 1) currt_page--;
            break;
        case 0:
            research_state = 0;
            break;
        default:
            for (int i = 0; i < book_count; i++) {
                if (s_a_b_input == book_list[i].b_numb) {
                    if (strcmp(book_list[i].b_state, "available") == 0)
                    {
                        char temp[50];
                        sprintf(temp, " %d", book_list[i].b_numb);
                        strcpy(book_list[i].b_state, "borrowed");
                        printf("\n成功借出书籍，名为 %s ，此书现为 %s 状态\n", book_list[i].b_name, book_list[i].b_state);
                        if (strlen(user_list[ena_user].borrowed) == 0)
                        {
                            strcpy((user_list[ena_user].borrowed), book_list[i].b_name);
                            strcat((user_list[ena_user].borrowed), temp);
                        }
                        else {
                            strcat((user_list[ena_user].borrowed), "\n");
                            strcat((user_list[ena_user].borrowed), book_list[i].b_name);
                            strcat((user_list[ena_user].borrowed), temp);
                        }
                    }
                    else if (strcmp(book_list[i].b_state, "borrowed") == 0)
                    {
                        printf("\n名为 %s 书籍借出失败，此书现为 %s 状态\n", book_list[i].b_name, book_list[i].b_state);
                    }
                    Sleep(1000);
                    break;
                }
            }
            break;
        }
    }
}

int is_manager(int ena_user,int input_count)
{
    int i_m_input;
    if (user_list[ena_user].grade >=4)
    {
        printf("\n欢迎管理员 %s \n", user_list[ena_user].u_name);
    }
    else
    {
        printf("\n你的身份并非管理员,输入管理员密钥来获得临时管理员权限\n");
        scanf("%d", &i_m_input);
        if (i_m_input == MANGER_PASSWORD)
        {
            printf("\n欢迎，你已获得临时管理员权限\n");
            return 1;
        }
        else
        {
            printf("\n密钥不正确，这是第 %d 次尝试\n", input_count);
            return 0;
        }
    }
}

int manager_system(int ena_user)
{
    int m_s_state = 1;
    int choice_input;
    int matched = 0;
    int founded = 0;
    int founded_2 = 0;

    int dele_input;

    int b_choice_input;
    int b_numb_input;
    char b_name_input[30];
    char b_type_input[20];
    char auther_input[50];
    char publishing_input[50];
    char more_info_input[500];
    int b_state_input;

    int u_choice_input;
    int u_account;
    int u_password;
    int grade;
    char u_name_input[20];
    char borrowed[300];

    while (m_s_state)
    {
        int book_count = instances_book_count();
        int user_count = instances_user_count();
        printf("\n====================================================\n");
        printf("=========== 欢迎进入 xx 借阅系统管理员系统 =========\n");
        printf("1. 增加图书信息\n");
        printf("2. 删除图书信息\n");
        printf("3. 修改图书信息\n");
        printf("4. 增加人员信息\n");
        printf("5. 删除人员信息\n");
        printf("6. 修改人员信息\n");
        printf("7. 恢复书籍原始数据\n");
        printf("8. 恢复人员原始数据\n");
        printf("9. 清空日志\n");
        printf("0. 退出管理员系统\n");
        printf("====================================================\n");
        scanf("%d", &choice_input);
        switch (choice_input)
        {
        case 1:
            founded = 0;
            sentry_add(ena_user,0);
            printf("\n==================正在进行书籍增加==================\n");
            printf("1/6.书籍编号添加\n");
            scanf("%d", &b_numb_input);
            for (int i = 0; i < book_count; i++)
            {
                if (b_numb_input == book_list[i].b_numb)
                {
                    printf("\n错误，编号 %d 书籍 %s 已存在\n", book_list[i].b_numb, book_list[i].b_name);
                    founded = 1;
                    break;
                }
            }
            if (founded == 1)
            {
                printf("正在返回管理员界面\n");
                break;
            }
            printf("2/6.书籍名称添加\n");
            scanf("%s", b_name_input);
            printf("3/6.书籍类型添加\n");
            scanf("%s", b_type_input);
            printf("4/6.书籍简介添加\n");
            scanf("%s", more_info_input);
            printf("5/6.书籍作者添加\n");
            scanf("%s", auther_input);
            printf("6/6.书籍出版社添加\n");
            scanf("%s", publishing_input);
            book_date_change(ena_user,book_count,b_numb_input, b_name_input, b_type_input, more_info_input, auther_input, publishing_input,1);
            printf("\n第 %d 本书籍创建成功，信息如下\n",book_count+1);
            printf("====================================================\n");
            printf("书籍编号: %d \n", book_list[book_count].b_numb);
            printf("书籍名称: %s \n", book_list[book_count].b_name);
            printf("书籍类型: %s \n", book_list[book_count].b_type);
            printf("书籍简介: %s \n", book_list[book_count].more_info);
            printf("书籍作者: %s \n", book_list[book_count].auther);
            printf("书籍出版社: %s \n", book_list[book_count].publishing);
            printf("书籍状态: %s \n", book_list[book_count].b_state);
            printf("====================================================\n");
            break;
        case 2:
            founded = 0;
            printf("\n==================正在进行书籍删除==================\n");
            printf("输入删除的书籍编号\n");
            scanf("%d", &dele_input);
            for (int i = 0; i < book_count; i++)
            {
                if (dele_input == book_list[i].b_numb)
                {
                    printf("找到书名为 %s 书籍进行删除\n", book_list[i].b_name);
                    matched = i;
                    founded = 1;
                    break;
                }
            }
            if (founded == 0)
            {
                printf("找不到编号为 %d 的书籍\n", dele_input);
                printf("正在返回管理员界面\n");
                break;
            }
            if (founded)
            {
                for (int i = matched; i < book_count; i++)
                {
                    strcpy(book_list[i].auther, book_list[i + 1].auther);
                    strcpy(book_list[i].b_name, book_list[i + 1].b_name);
                    strcpy(book_list[i].b_type, book_list[i + 1].b_type);
                    strcpy(book_list[i].more_info, book_list[i + 1].more_info);
                    strcpy(book_list[i].b_state, book_list[i + 1].b_state);
                    strcpy(book_list[i].publishing, book_list[i + 1].publishing);
                    book_list[i].b_numb = book_list[i + 1].b_numb;
                }
            }
            char log_detail[500];
            sprintf(log_detail, "%d 级用户 %s 在 %d 位置对书籍信息进行删除", user_list[ena_user].grade, user_list[ena_user].u_name, matched);
            log_message("书籍删除", log_detail);
            save_books();
            break;
        case 3:
            founded = 0;
            printf("\n==================正在进行书籍修改==================\n");
            printf("0/7.输入修改的书籍编号\n");
            scanf("%d", &b_choice_input);
            for (int i = 0; i < book_count; i++)
            {
                if (b_choice_input == book_list[i].b_numb)
                {
                    printf("找到书名为 %s 书籍进行修改\n", book_list[i].b_name);
                    matched = i;
                    founded = 1;
                    break;
                }
            }
            if (founded == 0)
            {
                printf("找不到编号为 %d 的书籍\n", b_choice_input);
                printf("正在返回管理员界面\n");
                break;
            }
            printf("1/7.当前书籍编号 %d \n书籍编号修改为\n",book_list[matched].b_numb);
            scanf("%d", &b_numb_input);
            printf("2/7.当前书籍名称 %s \n书籍编号名称为\n", book_list[matched].b_name);
            scanf("%s", b_name_input);
            printf("3/7.当前书籍类型 %s \n书籍编号类型为\n", book_list[matched].b_type);
            scanf("%s", b_type_input);
            printf("4/7.当前书籍简介 %s \n书籍编号简介为\n", book_list[matched].more_info);
            scanf("%s", more_info_input);
            printf("5/7.当前书籍作者 %s \n书籍编号作者为\n", book_list[matched].auther);
            scanf("%s", auther_input);
            printf("6/7.当前书籍出版社 %s \n书籍编号出版社为\n", book_list[matched].publishing);
            scanf("%s", publishing_input);
            printf("7/7.书籍状态修改(1表示为有效，0表示为借出)\n");
            printf("当前书籍状态 %s \n修改书籍编号状态为\n", book_list[matched].b_state);
            scanf("%d", &b_state_input);
            book_date_change(ena_user, matched, b_numb_input, b_name_input, b_type_input, more_info_input, auther_input, publishing_input, b_state_input);
            break;
        case 4:
            founded = 0;
            sentry_add(ena_user,1);
            printf("\n==================正在进行人员增加==================\n");
            printf("1/4.人员账号添加\n");
            scanf("%d", &u_account);
            for (int i = 0; i < user_count; i++)
            {
                if (u_account == user_list[i].u_account)
                {
                    printf("\n错误，编号 %d 人员 %s 已存在\n", user_list[i].u_account, user_list[i].u_name);
                    founded = 1;
                    break;
                }
            }
            if (founded == 1)
            {
                printf("正在返回管理员界面\n");
                break;
            }
            printf("2/4.人员密码添加\n");
            scanf("%d", &u_password);
            printf("3/4.人员等级添加\n");
            scanf("%d", &grade);
            printf("4/4.人员姓名添加\n");
            scanf("%s", u_name_input);
            user_date_change(ena_user, user_count, u_account, u_password, grade, u_name_input, "");
            printf("\n第 %d 位人员创建成功，信息如下\n",user_count+1);
            printf("====================================================\n");
            printf("人员账号: %d \n", user_list[user_count].u_account);
            printf("人员密码: %d \n", user_list[user_count].u_password);
            printf("人员等级: %d \n", user_list[user_count].grade);
            printf("人员姓名: %s \n", user_list[user_count].u_name);
            printf("人员租借状态: %s \n", user_list[user_count].borrowed);
            printf("====================================================\n");
            break;
        case 5:
            founded = 0;
            printf("==================正在进行人员删除==================\n");
            printf("删除的人员编号:\n");
            scanf("%d", &dele_input);
            for (int i = 0; i < user_count; i++)
            {
                if (dele_input == user_list[i].u_account)
                {
                    printf("找到编号为 %d 人员进行删除\n", user_list[i].u_account);
                    matched = i;
                    founded = 1;
                    break;
                }
            }
            if (founded == 0)
            {
                printf("找不到编号为 %d 的人员\n", dele_input);
                printf("正在返回管理员界面\n");
                break;
            }
            if (founded)
            {
                for (int i = matched; i < user_count; i++)
                {
                    strcpy(user_list[i].u_name, user_list[i+1].u_name);
                    strcpy(user_list[i].borrowed, user_list[i+1].borrowed);
                    user_list[i].grade = user_list[i + 1].grade;
                    user_list[i].u_account = user_list[i + 1].u_account;
                    user_list[i].u_password = user_list[i + 1].u_password;
                }
            }
            sprintf(log_detail, "%d 级用户 %s 在 %d 位置对人员信息进行删除", user_list[ena_user].grade, user_list[ena_user].u_name, matched);
            log_message("人员删除", log_detail);
            save_books();
            if (ena_user == matched)
            {
                printf("\n你的个人信息发生变动，请重新登录\n");
                return ena_user - 1;
            }
            break;
        case 6:
            founded = 0;
            founded_2 = 0;
            printf("==================正在进行人员修改==================\n");
            printf("0/5.修改的人员编号:\n");
            scanf("%d", &u_choice_input);
            for (int i = 0; i < user_count; i++)
            {
                if (u_choice_input == user_list[i].u_account)
                {
                    printf("找到编号为 %d 人员进行修改\n", user_list[i].u_account);
                    matched = i;
                    founded = 1;
                    break;
                }
            }
            if (founded == 0)
            {
                printf("找不到编号为 %d 的人员\n", u_choice_input);
                printf("正在返回管理员界面\n");
                break;
            }
            printf("1/5.当前人员编号 %d \n人员账号修改\n", user_list[matched].u_account);
            scanf("%d", &u_account);
            for (int i = 0; i < user_count; i++)
            {
                if (u_account == user_list[i].u_account && u_account != user_list[ena_user].u_account)
                {
                    printf("\n错误，该编号已被 %s 占用\n", user_list[i].u_name);
                    printf("正在返回管理员界面\n"); 
                    founded_2 = 1;
                }
            }
            if (founded_2)
            {
                break;
            }
            printf("2/5.当前人员密码 %d \n人员密码修改\n", user_list[matched].u_password);
            scanf("%d", &u_password);
            printf("3/5.当前人员等级 %d \n人员等级修改\n", user_list[matched].grade);
            scanf("%d", &grade);
            printf("4/5.当前人员姓名 %s \n人员姓名修改\n", user_list[matched].u_name);
            scanf("%s", u_name_input);
            printf("5/5.当前人员已借阅图书 %s \n人员已借阅图书修改\n", user_list[matched].borrowed);
            scanf("%s", borrowed);
            user_date_change(ena_user,matched, u_account, u_password, grade, u_name_input, borrowed);
            if (ena_user == matched)
            {
                printf("\n你的个人信息发生变动，请重新登录\n");
                return ena_user - 1;
            }
            break;
        case 7:
            remove("books.dat");
            printf("\n书籍本地损坏文件已删除，将重新生成本地文件\n");
            reset_books_to_default();
            save_books();
            break;
        case 8:

            remove("users.dat");
            printf("\n人员本地损坏文件已删除，将重新生成本地文件\n");
            save_users();
            reset_users_to_default();
            printf("\n人员认证已重置，正在重新进入认证系统\n\n");
            return -1;
            break;
        case 9:
            remove("log.txt");
            printf("\n本地日志文件已删除\n");
            break;
        case 0:
            m_s_state = 0;
            break;
        default:
            printf("\n输入有误\n");
            break;
        }
    }
    return 0;
}

void book_date_change(int ena_user, int pos, int b_numb, char b_name[], char b_type[], char more_info[], char auther[], char publisling[], int b_state)
{
    char ena_name[50];
    int ena_grade = (ena_user >= 0) ? user_list[ena_user].grade : 0; 
    if (ena_user >= 0) {
        strcpy(ena_name, user_list[ena_user].u_name);
    }
    else {
        strcpy(ena_name, "系统");
    }

    book_list[pos].b_numb = b_numb;
    strcpy(book_list[pos].b_name, b_name);
    strcpy(book_list[pos].b_type, b_type);
    strcpy(book_list[pos].more_info, more_info);
    strcpy(book_list[pos].auther, auther);
    strcpy(book_list[pos].publishing, publisling);
    strcpy(book_list[pos].b_state, b_state ? "available" : "borrowed");

    char log_detail[500];
    sprintf(log_detail, "%d 级用户 %s 在 %d 位置对书籍信息进行修改或添加, 变更后编号为 %d, 名字为 %s, 类型为 %s, 介绍为 %s, 作者为 %s, 出版社为 %s",
        ena_grade, ena_name, pos, b_numb, b_name, b_type, more_info, auther, publisling);

    log_message("书籍修改", log_detail);
    save_books();
}

void user_date_change(int ena_user, int pos, int u_account, int u_password, int grade, char u_name_input[], char borrowed[])
{
    char ena_name[50];
    int ena_grade = (ena_user >= 0) ? user_list[ena_user].grade : 0;
    if (ena_user >= 0) {
        strcpy(ena_name, user_list[ena_user].u_name);
    }
    else {
        strcpy(ena_name, "系统");
    }

    user_list[pos].u_account = u_account;
    user_list[pos].u_password = u_password;
    user_list[pos].grade = grade;
    strcpy(user_list[pos].u_name, u_name_input);
    strcpy(user_list[pos].borrowed, borrowed);

    char log_detail[500];
    sprintf(log_detail, "%d 级用户 %s 在 %d 位置对人员信息进行修改或添加, 变更后编号为 %d, 密码为 %d, 姓名为 %s, 等级为 %d, 借阅情况为 %s",
        ena_grade, ena_name, pos, u_account, u_password, u_name_input, grade, borrowed);

    log_message("用户修改", log_detail);
    save_users();
}

void sentry_add(int ena_user, int user_or_book)
{
    int user_sentry_pos = instances_user_count() + 1;
    int book_sentry_pos = instances_book_count() + 1;

    if (user_or_book) {
        user_date_change(-1, user_sentry_pos, -1, 0, 0, "", "");
    }
    else {
        book_date_change(-1, book_sentry_pos, -1, "", "", "", "", "", 0);
    }
}

void save_books() 
{
    FILE* fp = fopen("books.dat", "wb");
    if (!fp)
    {
        perror("\n书籍数据保存失败\n");
        return;
    }

    int count = instances_book_count();
    fwrite(&count, sizeof(int), 1, fp);
    fwrite(book_list, sizeof(struct Books), count, fp);

    fclose(fp);
}

void load_books() 
{
    FILE* fp = fopen("books.dat", "rb");
    if (!fp) return;

    int count = 0;
    fread(&count, sizeof(int), 1, fp);

    if (count > 0 && count < 10000) 
    {
        fread(book_list, sizeof(struct Books), count, fp);
        book_list[count].b_numb = -1;
    }

    fclose(fp);
}

void save_users()
{ 
    FILE* fp = fopen("users.dat", "wb");
    if (!fp)
    {
        printf("\n用户数据保存失败\n");
        return;
    }
    int count = instances_user_count();
    fwrite(&count, sizeof(int), 1, fp);
    fwrite(user_list, sizeof(struct Users), count, fp);

    fclose(fp);
}

void load_users()
{
    FILE* fp = fopen("users.dat", "rb");
    if (!fp)
    {
        return;
    }
    int count = 0;
    fread(&count, sizeof(int), 1, fp);

    if (count >0 && count <10000)
    {
        fread(user_list, sizeof(struct Users), count, fp);
        user_list[count].u_account = -1;
    }
    fclose(fp);
}

void reset_books_to_default() {
    struct Books default_books[1000] = {
        {1001, "C Programming", "Education", "available", "Brian Kernighan", "Prentice Hall", "A fundamental book on C language."},
        {1002, "The Great Gatsby", "Fiction", "borrowed", "F. Scott Fitzgerald", "Scribner", "A classic novel set in the 1920s."},
        {1003, "Data Structures & Algorithms", "Education", "available", "Robert Lafore", "SAMS Publishing", "Comprehensive guide on algorithms."},
        {1004, "1984", "Dystopian", "available", "George Orwell", "Secker & Warburg", "A novel about totalitarian surveillance."},
        {5, "To Kill a Mockingbird", "Fiction", "available", "Harper Lee", "J.B. Lippincott & Co.", "A novel about racial injustice in America."},
        {1006, "Introduction to Algorithms", "Education", "borrowed", "Cormen et al.", "MIT Press", "A widely used textbook on algorithms."},
        {1007, "The Catcher in the Rye", "Fiction", "available", "J.D. Salinger", "Little, Brown and Company", "A novel about teenage angst."},
        {1008, "Brave New World", "Dystopian", "available", "Aldous Huxley", "Chatto & Windus", "A dystopian novel about a future society."},
        {1009, "Artificial Intelligence", "Education", "borrowed", "Stuart Russell", "Pearson", "An introduction to AI concepts."},
        {1010, "The Hobbit", "Fantasy", "available", "J.R.R. Tolkien", "George Allen & Unwin", "A fantasy novel about Bilbo Baggins' journey."},
        {-1, "", "", "", "", "", ""}
    };
    memcpy(book_list, default_books, sizeof(default_books));
}

void reset_users_to_default() {
    struct Users default_users[500] = {
        {1, 1, "jujuj", 5, ""},
        {2, 2, "mmcy", 2, ""},
        {103, 9876, "Charlie", 3, ""},
        {104, 5432, "David", 4, ""},
        {105, 6789, "Eve", 5, ""},
        {106, 1122, "Frank", 2, ""},
        {107, 3344, "Grace", 3, ""},
        {108, 5566, "Hannah", 4, ""},
        {109, 7788, "Ivan", 5, ""},
        {110, 9900, "Jack", 1, ""},
        {-1, 0, "", 0, ""}
    };
    memcpy(user_list, default_users, sizeof(default_users));
}

void log_message(const char* action, const char* details)
{
    FILE* logfile = fopen("log.txt", "a");
    if (!logfile) {
        perror("创建或打开日志文件出错");
        return;
    }

    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);

    fprintf(logfile, "[%04d-%02d-%02d %02d:%02d:%02d] %s: %s\n",
        tm_info->tm_year + 1900, tm_info->tm_mon + 1, tm_info->tm_mday,
        tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec, action, details);
    printf("\n日志正在记录修改信息\n");
    fclose(logfile);
}

int main() {
    load_books();
    load_users();
    if (book_list[0].b_numb == -1) {
        save_books();
        save_users();
    }
    int main_state = 1;
    while (main_state)
    {
        int ena_user = censor();
        if (ena_user == -1)
        {
            main_state = 0;
        }
        int choice_input;
        int input_count = 1;
        while (ena_user >= 0) {
            printf("\n========================================\n");
            printf("=========== 欢迎进入xx借阅系统 =========\n");
            printf("1. 查询所有图书信息\n");
            printf("2. 查看我的信息\n");
            printf("3. 根据书名进行关键字搜索\n");
            printf("4. 进入管理员系统\n");
            printf("0. 返回登录页面\n");
            printf("========================================\n");
            scanf("%d", &choice_input);
            switch (choice_input) {
            case 1:
                show_all_book(ena_user);
                break;
            case 2:
                show_myself(ena_user);
                break;
            case 3:
                show_matched_book(ena_user);
                break;
            case 4:
                if (is_manager(ena_user, input_count))
                {
                    ena_user= manager_system(ena_user);
                }
                else
                {
                    input_count++;
                }
                break;
            case 0:
                ena_user = -1;
                break;
            default:
                printf("错误输入或暂无该功能！\n");
                break;
            }
        }
        ena_user = 0;
    }
    save_books();
    save_users();
    return 0;
}
