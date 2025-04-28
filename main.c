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
        printf("��������ͼ����xx����ϵͳ��������֤������\n(����0���˳�����ϵͳ)\n�˺ţ�\n");
        scanf("%d", &account_input);
        if (account_input == 0)
        {
            return -1;
        }
        printf("���룺\n");
        scanf("%d", &password_input);
        for (int i = 0; i < user_count; i++) {
            if (account_input == user_list[i].u_account && password_input == user_list[i].u_password) {
                ena_index = i;
                printf("��ӭ��%s\n��������ϵͳ\n", user_list[ena_index].u_name);
                return ena_index;
            }
        }
        printf("\n�˻����������\n");
    }
}

void show_all_book(int ena_user) {
    int book_count = instances_book_count();
    int currt_page = 1;
    int total_page = (book_count + 4) / 5;

    while (1) {
        for (int i = (currt_page - 1) * 5; i < currt_page * 5 && i < book_count; i++) {
            printf("\n=====��%d/%d�� ͼ����Ϣ ========\n", i + 1, book_count);
            printf("������%s\n", book_list[i].b_name);
            printf("���ߣ�%s\n", book_list[i].auther);
            printf("�����磺%s\n", book_list[i].publishing);
            printf("��ţ�%d\n", book_list[i].b_numb);
            printf("���ͣ�%s\n", book_list[i].b_type);
            printf("״̬��%s\n", book_list[i].b_state);
            printf("================================\n\n");
        }

        printf("=========== ѡ�� =========\n");
        printf("��ǰ�� %d/%d ҳ\n", currt_page, total_page);
        if (currt_page < total_page) {
            printf("1. ��һҳ\n");
        }
        if (currt_page > 1) {
            printf("2. ��һҳ\n");
        }
        printf("0. ����������\n");
        printf("�������鼮��ű�ʾ����\n");
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
                        printf("\n�ɹ�����鼮����Ϊ %s ��������Ϊ %s ״̬\n", book_list[i].b_name, book_list[i].b_state);
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
                        printf("\n��Ϊ %s �鼮���ʧ�ܣ�������Ϊ %s ״̬\n", book_list[i].b_name, book_list[i].b_state);
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
        printf("\n================�ҵ���Ϣ================\n");
        printf("����: %s\n", user_list[user_index].u_name);
        printf("���: %d\n", user_list[user_index].u_account);
        printf("�ȼ�: %d\n", user_list[user_index].grade);
        printf("��/������ͼ��: %s\n", user_list[user_index].borrowed);
        printf("\n========================================\n");

        printf("=========== ѡ�� =========\n");
        printf("����������ɻ���\n");
        printf("0.������ҳ��\n");
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
                    printf("\n�黹�鼮 %s �ɹ�\n", book_list[i].b_name);
                    Sleep(1000);
                }
                else
                {
                    printf("\n����δ���� %s \n", book_list[i].b_name);
                }
            }
        }
        if (found == 0 && s_m_input != 0)
        {
            printf("\nδ��ϵͳ���ҵ����Ϊ %d �鼮\n", s_m_input);
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

    printf("\n====== ��ӭ����xxϵͳ��Ѱ���� ========\n");
    printf("�����鼮�ؼ����Բ�ѯ��\n");
    printf("0.�˳���ѯ\n");
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
        printf("\nϵͳ��û�з����������鼮\n");
        research_state = 0;
    }
    int currt_page = 1;
    int total_page = (matched_count + 4) / 5;
    while (research_state) {
        for (int i = (currt_page - 1) * 5; i < currt_page * 5 && i < matched_count; i++) {
            printf("\n=====��%d/%d�� ͼ����Ϣ ========\n", i + 1, matched_count);
            printf("������%s\n", book_list[matched_list[i]].b_name);
            printf("���ߣ�%s\n", book_list[matched_list[i]].auther);
            printf("�����磺%s\n", book_list[matched_list[i]].publishing);
            printf("��ţ�%d\n", book_list[matched_list[i]].b_numb);
            printf("���ͣ�%s\n", book_list[matched_list[i]].b_type);
            printf("״̬��%s\n", book_list[matched_list[i]].b_state);
            printf("================================\n\n");
        }

        printf("=========== ѡ�� =========\n");
        printf("��ǰ�� %d/%d ҳ\n", currt_page, total_page);
        if (currt_page < total_page) {
            printf("1. ��һҳ\n");
        }
        if (currt_page > 1) {
            printf("2. ��һҳ\n");
        }
        printf("0. ����������\n");
        printf("�������鼮��ű�ʾ����\n");
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
                        printf("\n�ɹ�����鼮����Ϊ %s ��������Ϊ %s ״̬\n", book_list[i].b_name, book_list[i].b_state);
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
                        printf("\n��Ϊ %s �鼮���ʧ�ܣ�������Ϊ %s ״̬\n", book_list[i].b_name, book_list[i].b_state);
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
        printf("\n��ӭ����Ա %s \n", user_list[ena_user].u_name);
    }
    else
    {
        printf("\n�����ݲ��ǹ���Ա,�������Ա��Կ�������ʱ����ԱȨ��\n");
        scanf("%d", &i_m_input);
        if (i_m_input == MANGER_PASSWORD)
        {
            printf("\n��ӭ�����ѻ����ʱ����ԱȨ��\n");
            return 1;
        }
        else
        {
            printf("\n��Կ����ȷ�����ǵ� %d �γ���\n", input_count);
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
        printf("=========== ��ӭ���� xx ����ϵͳ����Աϵͳ =========\n");
        printf("1. ����ͼ����Ϣ\n");
        printf("2. ɾ��ͼ����Ϣ\n");
        printf("3. �޸�ͼ����Ϣ\n");
        printf("4. ������Ա��Ϣ\n");
        printf("5. ɾ����Ա��Ϣ\n");
        printf("6. �޸���Ա��Ϣ\n");
        printf("7. �ָ��鼮ԭʼ����\n");
        printf("8. �ָ���Աԭʼ����\n");
        printf("9. �����־\n");
        printf("0. �˳�����Աϵͳ\n");
        printf("====================================================\n");
        scanf("%d", &choice_input);
        switch (choice_input)
        {
        case 1:
            founded = 0;
            sentry_add(ena_user,0);
            printf("\n==================���ڽ����鼮����==================\n");
            printf("1/6.�鼮������\n");
            scanf("%d", &b_numb_input);
            for (int i = 0; i < book_count; i++)
            {
                if (b_numb_input == book_list[i].b_numb)
                {
                    printf("\n���󣬱�� %d �鼮 %s �Ѵ���\n", book_list[i].b_numb, book_list[i].b_name);
                    founded = 1;
                    break;
                }
            }
            if (founded == 1)
            {
                printf("���ڷ��ع���Ա����\n");
                break;
            }
            printf("2/6.�鼮�������\n");
            scanf("%s", b_name_input);
            printf("3/6.�鼮�������\n");
            scanf("%s", b_type_input);
            printf("4/6.�鼮������\n");
            scanf("%s", more_info_input);
            printf("5/6.�鼮�������\n");
            scanf("%s", auther_input);
            printf("6/6.�鼮���������\n");
            scanf("%s", publishing_input);
            book_date_change(ena_user,book_count,b_numb_input, b_name_input, b_type_input, more_info_input, auther_input, publishing_input,1);
            printf("\n�� %d ���鼮�����ɹ�����Ϣ����\n",book_count+1);
            printf("====================================================\n");
            printf("�鼮���: %d \n", book_list[book_count].b_numb);
            printf("�鼮����: %s \n", book_list[book_count].b_name);
            printf("�鼮����: %s \n", book_list[book_count].b_type);
            printf("�鼮���: %s \n", book_list[book_count].more_info);
            printf("�鼮����: %s \n", book_list[book_count].auther);
            printf("�鼮������: %s \n", book_list[book_count].publishing);
            printf("�鼮״̬: %s \n", book_list[book_count].b_state);
            printf("====================================================\n");
            break;
        case 2:
            founded = 0;
            printf("\n==================���ڽ����鼮ɾ��==================\n");
            printf("����ɾ�����鼮���\n");
            scanf("%d", &dele_input);
            for (int i = 0; i < book_count; i++)
            {
                if (dele_input == book_list[i].b_numb)
                {
                    printf("�ҵ�����Ϊ %s �鼮����ɾ��\n", book_list[i].b_name);
                    matched = i;
                    founded = 1;
                    break;
                }
            }
            if (founded == 0)
            {
                printf("�Ҳ������Ϊ %d ���鼮\n", dele_input);
                printf("���ڷ��ع���Ա����\n");
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
            sprintf(log_detail, "%d ���û� %s �� %d λ�ö��鼮��Ϣ����ɾ��", user_list[ena_user].grade, user_list[ena_user].u_name, matched);
            log_message("�鼮ɾ��", log_detail);
            save_books();
            break;
        case 3:
            founded = 0;
            printf("\n==================���ڽ����鼮�޸�==================\n");
            printf("0/7.�����޸ĵ��鼮���\n");
            scanf("%d", &b_choice_input);
            for (int i = 0; i < book_count; i++)
            {
                if (b_choice_input == book_list[i].b_numb)
                {
                    printf("�ҵ�����Ϊ %s �鼮�����޸�\n", book_list[i].b_name);
                    matched = i;
                    founded = 1;
                    break;
                }
            }
            if (founded == 0)
            {
                printf("�Ҳ������Ϊ %d ���鼮\n", b_choice_input);
                printf("���ڷ��ع���Ա����\n");
                break;
            }
            printf("1/7.��ǰ�鼮��� %d \n�鼮����޸�Ϊ\n",book_list[matched].b_numb);
            scanf("%d", &b_numb_input);
            printf("2/7.��ǰ�鼮���� %s \n�鼮�������Ϊ\n", book_list[matched].b_name);
            scanf("%s", b_name_input);
            printf("3/7.��ǰ�鼮���� %s \n�鼮�������Ϊ\n", book_list[matched].b_type);
            scanf("%s", b_type_input);
            printf("4/7.��ǰ�鼮��� %s \n�鼮��ż��Ϊ\n", book_list[matched].more_info);
            scanf("%s", more_info_input);
            printf("5/7.��ǰ�鼮���� %s \n�鼮�������Ϊ\n", book_list[matched].auther);
            scanf("%s", auther_input);
            printf("6/7.��ǰ�鼮������ %s \n�鼮��ų�����Ϊ\n", book_list[matched].publishing);
            scanf("%s", publishing_input);
            printf("7/7.�鼮״̬�޸�(1��ʾΪ��Ч��0��ʾΪ���)\n");
            printf("��ǰ�鼮״̬ %s \n�޸��鼮���״̬Ϊ\n", book_list[matched].b_state);
            scanf("%d", &b_state_input);
            book_date_change(ena_user, matched, b_numb_input, b_name_input, b_type_input, more_info_input, auther_input, publishing_input, b_state_input);
            break;
        case 4:
            founded = 0;
            sentry_add(ena_user,1);
            printf("\n==================���ڽ�����Ա����==================\n");
            printf("1/4.��Ա�˺����\n");
            scanf("%d", &u_account);
            for (int i = 0; i < user_count; i++)
            {
                if (u_account == user_list[i].u_account)
                {
                    printf("\n���󣬱�� %d ��Ա %s �Ѵ���\n", user_list[i].u_account, user_list[i].u_name);
                    founded = 1;
                    break;
                }
            }
            if (founded == 1)
            {
                printf("���ڷ��ع���Ա����\n");
                break;
            }
            printf("2/4.��Ա�������\n");
            scanf("%d", &u_password);
            printf("3/4.��Ա�ȼ����\n");
            scanf("%d", &grade);
            printf("4/4.��Ա�������\n");
            scanf("%s", u_name_input);
            user_date_change(ena_user, user_count, u_account, u_password, grade, u_name_input, "");
            printf("\n�� %d λ��Ա�����ɹ�����Ϣ����\n",user_count+1);
            printf("====================================================\n");
            printf("��Ա�˺�: %d \n", user_list[user_count].u_account);
            printf("��Ա����: %d \n", user_list[user_count].u_password);
            printf("��Ա�ȼ�: %d \n", user_list[user_count].grade);
            printf("��Ա����: %s \n", user_list[user_count].u_name);
            printf("��Ա���״̬: %s \n", user_list[user_count].borrowed);
            printf("====================================================\n");
            break;
        case 5:
            founded = 0;
            printf("==================���ڽ�����Աɾ��==================\n");
            printf("ɾ������Ա���:\n");
            scanf("%d", &dele_input);
            for (int i = 0; i < user_count; i++)
            {
                if (dele_input == user_list[i].u_account)
                {
                    printf("�ҵ����Ϊ %d ��Ա����ɾ��\n", user_list[i].u_account);
                    matched = i;
                    founded = 1;
                    break;
                }
            }
            if (founded == 0)
            {
                printf("�Ҳ������Ϊ %d ����Ա\n", dele_input);
                printf("���ڷ��ع���Ա����\n");
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
            sprintf(log_detail, "%d ���û� %s �� %d λ�ö���Ա��Ϣ����ɾ��", user_list[ena_user].grade, user_list[ena_user].u_name, matched);
            log_message("��Աɾ��", log_detail);
            save_books();
            if (ena_user == matched)
            {
                printf("\n��ĸ�����Ϣ�����䶯�������µ�¼\n");
                return ena_user - 1;
            }
            break;
        case 6:
            founded = 0;
            founded_2 = 0;
            printf("==================���ڽ�����Ա�޸�==================\n");
            printf("0/5.�޸ĵ���Ա���:\n");
            scanf("%d", &u_choice_input);
            for (int i = 0; i < user_count; i++)
            {
                if (u_choice_input == user_list[i].u_account)
                {
                    printf("�ҵ����Ϊ %d ��Ա�����޸�\n", user_list[i].u_account);
                    matched = i;
                    founded = 1;
                    break;
                }
            }
            if (founded == 0)
            {
                printf("�Ҳ������Ϊ %d ����Ա\n", u_choice_input);
                printf("���ڷ��ع���Ա����\n");
                break;
            }
            printf("1/5.��ǰ��Ա��� %d \n��Ա�˺��޸�\n", user_list[matched].u_account);
            scanf("%d", &u_account);
            for (int i = 0; i < user_count; i++)
            {
                if (u_account == user_list[i].u_account && u_account != user_list[ena_user].u_account)
                {
                    printf("\n���󣬸ñ���ѱ� %s ռ��\n", user_list[i].u_name);
                    printf("���ڷ��ع���Ա����\n"); 
                    founded_2 = 1;
                }
            }
            if (founded_2)
            {
                break;
            }
            printf("2/5.��ǰ��Ա���� %d \n��Ա�����޸�\n", user_list[matched].u_password);
            scanf("%d", &u_password);
            printf("3/5.��ǰ��Ա�ȼ� %d \n��Ա�ȼ��޸�\n", user_list[matched].grade);
            scanf("%d", &grade);
            printf("4/5.��ǰ��Ա���� %s \n��Ա�����޸�\n", user_list[matched].u_name);
            scanf("%s", u_name_input);
            printf("5/5.��ǰ��Ա�ѽ���ͼ�� %s \n��Ա�ѽ���ͼ���޸�\n", user_list[matched].borrowed);
            scanf("%s", borrowed);
            user_date_change(ena_user,matched, u_account, u_password, grade, u_name_input, borrowed);
            if (ena_user == matched)
            {
                printf("\n��ĸ�����Ϣ�����䶯�������µ�¼\n");
                return ena_user - 1;
            }
            break;
        case 7:
            remove("books.dat");
            printf("\n�鼮�������ļ���ɾ�������������ɱ����ļ�\n");
            reset_books_to_default();
            save_books();
            break;
        case 8:

            remove("users.dat");
            printf("\n��Ա�������ļ���ɾ�������������ɱ����ļ�\n");
            save_users();
            reset_users_to_default();
            printf("\n��Ա��֤�����ã��������½�����֤ϵͳ\n\n");
            return -1;
            break;
        case 9:
            remove("log.txt");
            printf("\n������־�ļ���ɾ��\n");
            break;
        case 0:
            m_s_state = 0;
            break;
        default:
            printf("\n��������\n");
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
        strcpy(ena_name, "ϵͳ");
    }

    book_list[pos].b_numb = b_numb;
    strcpy(book_list[pos].b_name, b_name);
    strcpy(book_list[pos].b_type, b_type);
    strcpy(book_list[pos].more_info, more_info);
    strcpy(book_list[pos].auther, auther);
    strcpy(book_list[pos].publishing, publisling);
    strcpy(book_list[pos].b_state, b_state ? "available" : "borrowed");

    char log_detail[500];
    sprintf(log_detail, "%d ���û� %s �� %d λ�ö��鼮��Ϣ�����޸Ļ����, �������Ϊ %d, ����Ϊ %s, ����Ϊ %s, ����Ϊ %s, ����Ϊ %s, ������Ϊ %s",
        ena_grade, ena_name, pos, b_numb, b_name, b_type, more_info, auther, publisling);

    log_message("�鼮�޸�", log_detail);
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
        strcpy(ena_name, "ϵͳ");
    }

    user_list[pos].u_account = u_account;
    user_list[pos].u_password = u_password;
    user_list[pos].grade = grade;
    strcpy(user_list[pos].u_name, u_name_input);
    strcpy(user_list[pos].borrowed, borrowed);

    char log_detail[500];
    sprintf(log_detail, "%d ���û� %s �� %d λ�ö���Ա��Ϣ�����޸Ļ����, �������Ϊ %d, ����Ϊ %d, ����Ϊ %s, �ȼ�Ϊ %d, �������Ϊ %s",
        ena_grade, ena_name, pos, u_account, u_password, u_name_input, grade, borrowed);

    log_message("�û��޸�", log_detail);
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
        perror("\n�鼮���ݱ���ʧ��\n");
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
        printf("\n�û����ݱ���ʧ��\n");
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
        perror("���������־�ļ�����");
        return;
    }

    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);

    fprintf(logfile, "[%04d-%02d-%02d %02d:%02d:%02d] %s: %s\n",
        tm_info->tm_year + 1900, tm_info->tm_mon + 1, tm_info->tm_mday,
        tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec, action, details);
    printf("\n��־���ڼ�¼�޸���Ϣ\n");
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
            printf("=========== ��ӭ����xx����ϵͳ =========\n");
            printf("1. ��ѯ����ͼ����Ϣ\n");
            printf("2. �鿴�ҵ���Ϣ\n");
            printf("3. �����������йؼ�������\n");
            printf("4. �������Աϵͳ\n");
            printf("0. ���ص�¼ҳ��\n");
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
                printf("������������޸ù��ܣ�\n");
                break;
            }
        }
        ena_user = 0;
    }
    save_books();
    save_users();
    return 0;
}
