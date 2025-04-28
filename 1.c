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
