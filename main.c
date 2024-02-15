#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <time.h> //rand(),sand(),time_t,curtime
#include "user.c"

char sym_list[100][100];
char tab_list[100][100];
int tab_QTY[100];
int link[100];
int bill_no = 100;
int id;
float sales = 0;
FILE *fptr;
void bill(int prices[], int tab_ct);
void format(char s[]);
void reset_list();
void print_sbar(char s[]);
int get_symptoms();
void predict_medicine(int sym_ct);
int generate_medicine(int sym_ct);
int get_tablets();
int *get_prices(int n);
void print_logo(int t);
void login_page();
void search_sym_med();

void add_p();
// void add_p_data();
void print_bill_head();
struct patient // creates a new structure for patient details
{
    char p_name[20];
    int p_age;
    int p_bill_no;
    char gender;
    struct patient *next;
} patient_add;
struct tablet // creates a new structure for patient details
{
    char name[100];
    int quantity;
    float price;
    struct date
    {
        int mm;
        int yy;
    } dd;
};
// } *ptr, *new_p, *head = NULL;

void print_logo(int t)
{
    if (t == 0)
    {
        system("cls");
        printf("\x1b[1;31m"); // for bold,red colour
        FILE *ptr = fopen("LOGO.txt", "r");
        char ch;
        int ct = 0;
        while (ch != EOF)
        {
            ct++;
            ch = fgetc(ptr);
            printf("%c", ch);
            if (ct % 4 == 0)
                Sleep(3);
        }
        printf("\x1b[2;0m"); // for normal colors
        // printf("\n\n\n\t\t\tPress any Key to Continue");
        // getch();
        fflush(stdin);
    }
    else
    {
        system("cls");
        printf("\x1b[1;31m"); // for bold,red colour
        FILE *ptr = fopen("LOGO.txt", "r");
        char ch;
        int ct = 0;
        while (ch != EOF)
        {
            ct++;
            ch = fgetc(ptr);
            printf("%c", ch);
        }
        printf("\x1b[2;0m"); // for normal colors
        // printf("\n\n\n\t\t\tPress any Key to Continue");
        // getch();
        fflush(stdin);
    }
}

void login_page()
{
    // search_sym_med();
    int k = 0;
    int id;         // user ID (user 1,user 2,user 3)
    char pword[10]; // user passwords are in user.c
    system("cls");
    print_logo(0);
user_login: // login page
    printf("\n\n");
    printf("\t\t\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
    printf("\t\t\t\t\t\t\t\xdb\xdb            \xdb\xdb\n");
    printf("\t\t\t\t\t\t\t\xdb\xdb User login \xdb\xdb\n");
    printf("\t\t\t\t\t\t\t\xdb\xdb            \xdb\xdb\n");
    printf("\t\t\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n\n\n");
    printf("\t\t\t\t\t.------------------------------------------.\n");
    printf("\t\t\t\t\t|    For Guest Entry : user1 & 1234 !!!    |\n");
    printf("\t\t\t\t\t'------------------------------------------'\n");
    printf("\n\n\t\t\t\t\tEnter ID       : "); // user 1, user 2, user 3;
    fflush(stdin);
    scanf("user%d", &id);

    fflush(stdin);
    printf("\n\t\t\t\t\tEnter Password : ");
    int i = 0;
    char c;
    int pass_size = 0;
    while (pass_size < 7) // To hide password...
    {
        pword[pass_size] = getch();
        if (pword[pass_size] == '\r')
        {
            pword[pass_size] = '\0';
            break;
        }
        else if (pword[pass_size] == '\b')
        {
            if (pass_size > 0)
            {
                pass_size--;
                printf("\b \b");
            }
        }
        else
        {
            printf("*");
            pass_size++;
        }
    }
    if (password(id, pword)) // check whether the  user id and password are correct
    {
        k = 1;
        time_t curtime;
        time(&curtime);
        FILE *fp;
        fp = fopen("history.txt", "a"); // to note entry of user in the history
        fprintf(fp, "User %d\nLOG-IN: %s", id, ctime(&curtime));
        fclose(fp);
        int select;
    service: // HOME page....
        system("cls");
        print_logo(1);
        printf("\n");
        // printf("\t\t\t\t\t\t\t Choose a Service:\n");
    }
    // return k;

    // k = login_page();
    if (k == 0)
    {
        printf("\n\n\t\t\t\t\tWrong Password or User ID\n");
        printf("\t\t\t\t\tPress any key to continue...");
        getch();
        fflush(stdin);
        print_logo(1);
        goto user_login;
    }
    else
    {
        // system("cls");
        search_sym_med();
    }
}

void bill(int prices[], int tab_ct)
{ // generates bill for selected tablets
    system("cls");
    printf("-------------------------------------------------------------------------------------\n");
    printf("      Tablet                                   price/10       QTY       Final Price                        \n\n");
    for (int i = 0; i < tab_ct; i++)
    {
        printf("    ");
        int k = 0;
        for (int j = 0; j < 45; j++)
        {
            if (k == 0)
            {
                if (tab_list[i][j] == '\0')
                    k = 1;
                printf("%c", tab_list[i][j]);
            }
            else
            {
                printf(" ");
            }
        }
        printf("%d", prices[i]);
        printf("           %d       %.2f\n", tab_QTY[i], tab_QTY[i] * (prices[i] / 10.0));
    }
    printf("-------------------------------------------------------------------------------------\n");
}

void format(char s[])
{ // selects a tablets if multiple tablets are suits for the selected symptom
    int n = strlen(s);
    for (int i = 0; i < n; i++)
    {
        if (s[i] == '|')
        {
            s[i - 1] = '\0';
            break;
        }
    }
}

void reset_list()
{
    for (int i = 0; i < 100; i++)
    {
        strcpy(tab_list[i], "");
    }
}

void print_sbar(char s[]) // prints Search Bar
{

   
    printf("\t\t\t\t\t---------------------------------\n");
    printf("\t\t\t\t\t\x1b[1;33m%s|                          \n", s);
    printf("\x1b[0;39m");
    printf("\t\t\t\t\t---------------------------------\n\n\n");
    // printf("\x1b[1;31m");
}

int get_symptoms() // To input symptoms
{
    int ct = 0, k = 0, snum = 0, ch, line_ct = 0;
    char input_sym[100], file_sym[100];
    strcpy(input_sym, "");
    system("cls");
    printf("\n\n\t\t\t\t\tEnter Symptoms: \n\n");
    print_sbar(input_sym);
    strcpy(sym_list, "");
    while ((ch = _getch()) != 27)
    { // Loop until the Esc key is pressed (ASCII value 27)
        if (ch == 0 || ch == 224)
        {                  // Check for extended key
            ch = _getch(); // Get the extended key code

            if (ch == 72)
            {
                // printf("Up arrow key pressed\n");
                if (line_ct > 0)
                    line_ct--;
                system("cls");
                printf("\n\n\t\t\t\t\tEnter Symptoms: \n\n");
                print_sbar(input_sym);
                goto matches;
            }
            else if (ch == 80)
            {
                // printf("Down arrow key pressed\n");
                line_ct++;
                system("cls");
                printf("\n\n\t\t\t\t\tEnter Symptoms: \n\n");
                print_sbar(input_sym);
                goto matches;
            }
        }
        else
        {
            system("cls");
            if (ch == 32)
            {
                line_ct = 0;
                if (k == 0)
                {
                    printf(" Please consult a doctor for \"%s\" Symptom (or) INVALID SYMPTOM !!\n\n", input_sym);
                    printf("Press any key to continue......");
                    char t = getch();
                    continue;
                }
                snum++;
                strcpy(input_sym, "");
                printf("\n\n\t\t\t\t\tEnter Symptoms: \n\n");
                print_sbar(input_sym);
                continue;
            }
            if (ch == 8)
            {
                int len = strlen(input_sym);
                input_sym[len - 1] = '\0';
                printf("\n\n\t\t\t\t\tEnter Symptoms: \n\n");
                print_sbar(input_sym);
                goto matches;
                // continue;
            }
            if (ch == 13)
                break;
            strncat(input_sym, &ch, 1);
            printf("\n\n\t\t\t\t\tEnter Symptoms: \n\n");
            print_sbar(input_sym);
            FILE *fp;
            char e;

        matches:
            fp = fopen("Symptoms.txt", "r");
            k = 0; // to scan only first symptom..
            int limit = 0;
            while (!feof(fp))
            {
                fscanf(fp, "%s", file_sym);
                if (strstr(file_sym, input_sym) && limit <= 7)
                {

                    if (limit == line_ct)
                    {
                        printf("\t\t\t\t\t>");

                        printf("\x1b[1;36m %s\x1b[22;0m\n", file_sym);
                        strcpy(sym_list[snum], file_sym);
                        k = 1;
                    }
                    else
                    {
                        printf("\t\t\t\t\t %s\n", file_sym);
                        printf(" ");
                    }
                    limit++;
                }
            }
        }
    }
    printf("Symptoms: ");
    if (snum == 0)
        printf("Empty!!\n");
    else
    {
        for (int h = 0; h < snum - 1; h++)
        {
            printf("\n\t %s", sym_list[h]);
        }
        printf("\n\t %s\n", sym_list[snum - 1]);
    }
    // printf("\e[?25h");
    return snum;
}

void predict_medicine(int sym_ct) // create links to selected symptom based on avaliable tablets
{
    int n = sym_ct;

    for (int i = 0; i < n; i++)
        link[i] = 0;
    int mx_ct = 0, prid_ct = 0, set[n];
    char c;
    for (int i = 0; i < n; i++)
        set[i] = 0;
    while (prid_ct < n)
    {
        int d_ct = 0;
        FILE *fp;
        fp = fopen("sortedmeds.txt", "r");
        while (1)
        {
            d_ct++;
            int id, p;
            char s1[300], s2[300], s3[300];
            fscanf(fp, "%d", &id);
            fscanf(fp, "%s", s1);
            fscanf(fp, "%s", s2);
            fscanf(fp, "%s", s3);
            fscanf(fp, "%d", &p);
            if (feof(fp))
            {
                break;
            }
            int temp_link[n];
            for (int i = 0; i < n; i++)
                temp_link[i] = 0;
            int m_ct = 0;
            for (int i = 0; i < n; i++)
            {
                if (set[i] != 0)
                    continue;
                if (strstr(s1, sym_list[i]))
                {
                    m_ct++;
                    temp_link[i] = d_ct;
                }
                if (mx_ct <= m_ct)
                {
                    for (int i = 0; i < n; i++)
                    {
                        if (set[i] == 0)
                            link[i] = temp_link[i];
                    }
                    mx_ct = m_ct;
                }
            }
        }
        fclose(fp);
        mx_ct = 0;
        for (int i = 0; i < n; i++)
        {
            if (link[i] > 0)
                set[i] = 1;
        }
        prid_ct = 0;
        for (int i = 0; i < n; i++)
        {
            if (link[i] > 0)
                prid_ct++;
        }
    }
    // for (int i = 0; i < n; i++)
    // {
    //     printf("%d ", link[i]);
    // }
    // printf("\n");
}

int generate_medicine(int sym_ct)
{ // generates medicines list based on links created
    int i = 0;
    reset_list();
    int hash[50] = {0};
    for (int i = 0; i < sym_ct; i++)
    {
        hash[link[i]]++;
    }
    // printf("\n");
    // for(int i=0;i<40;i++){
    //     printf("%d ",hash[i]);
    // }
    FILE *fp;
    int d_ct = 0;
    fp = fopen("sortedmeds.txt", "r");
    while (1)
    {
        d_ct++;
        int id, p;
        char s1[300], s2[300], s3[300];
        fscanf(fp, "%d", &id);
        fscanf(fp, "%s", s1);
        fscanf(fp, "%s", s2);
        fscanf(fp, "%s", s3);
        fscanf(fp, "%d", &p);
        if (feof(fp))
        {
            break;
        }
        if (hash[d_ct] > 0)
        {
            format(s2);
            tab_QTY[i] = 1;
            strcpy(tab_list[i], s2);
            i++;
        }
    }
    fclose(fp);
    return i;
}

int get_tablets() // To input Medecines
{
    int ct = 0, k = 0, snum = 0, ch, line_ct = 0;
    char input_tab[100], file_tab[100];
    strcpy(input_tab, "");
    system("cls");
    printf("\n\n\t\t\t\t\tEnter tablets:\n\n");
    print_sbar(input_tab);
    strcpy(tab_list, "");
    while ((ch = _getch()) != 27)
    { // Loop until the Esc key is pressed (ASCII value 27)
        if (ch == 0 || ch == 224)
        {                  // Check for extended key
            ch = _getch(); // Get the extended key code

            if (ch == 72)
            {
                // printf("Up arrow key pressed\n");
                if (line_ct > 0)
                    line_ct--;
                system("cls");
                printf("\n\n\t\t\t\t\tEnter tablets:\n\n");
                print_sbar(input_tab);
                goto matches;
            }
            else if (ch == 80)
            {
                // printf("Down arrow key pressed\n");
                line_ct++;
                system("cls");
                printf("\n\n\t\t\t\t\tEnter tablets:\n\n");
                print_sbar(input_tab);
                goto matches;
            }
        }
        else
        {
            system("cls");
            if (ch == 32)
            {
                line_ct = 0;
                if (k == 0)
                {
                    printf(" Sorry \"%s\" Not Found (or) OUT OF STOCK !!\n\n", input_tab);
                    printf("Press any key to continue......");
                    char t = getch();
                    continue;
                }
                printf("\n%s: QTY >> ", tab_list[snum]);
                scanf("%d", &tab_QTY[snum]);
                snum++;
                strcpy(input_tab, "");
                printf("\n\n\t\t\t\t\tEnter tablets:\n\n");
                print_sbar(input_tab);
                continue;
            }
            if (ch == 8)
            {
                int len = strlen(input_tab);
                input_tab[len - 1] = '\0';
                printf("\n\n\t\t\t\t\tEnter tablets:\n\n");
                // if(len > 0) {
                // print_sbar(input_tab);
                // goto matches;
                // }else{
                // print_sbar(input_tab);

                // }
                print_sbar(input_tab);
                goto matches;
                // continue;
            }
            if (ch == 13)
                break;
            strncat(input_tab, &ch, 1);
            printf("\n\n\t\t\t\t\tEnter tablets:\n\n");
            print_sbar(input_tab);
            FILE *fp;
            char e;

        matches:
            fp = fopen("tablets_dataset.txt", "r");
            k = 0; // to scan only first tabptom..
            int limit = 0;
            while (!feof(fp))
            {
                fscanf(fp, "%s", file_tab);
                int id;
                fscanf(fp, "%d", &id);

                if (strstr(file_tab, input_tab) && limit <= 7)
                {

                    if (limit == line_ct)
                    {
                        printf("\t\t\t\t\t>");
                        printf("\x1b[1;36m %s\x1b[22;0m\n", file_tab);
                        strcpy(tab_list[snum], file_tab);
                        k = 1;
                    }
                    else
                    {
                        printf("\t\t\t\t\t %s\n", file_tab);
                        printf(" ");
                    }
                    limit++;
                }
            }
        }
    }
    printf("tablets: ");
    if (snum == 0)
        printf("Empty!!\n");
    else
    {
        for (int h = 0; h < snum - 1; h++)
        {
            printf("\n\t %s", tab_list[h]);
        }
        printf("\n\t %s\n", tab_list[snum - 1]);
    }
    // printf("\e[?25h");
    return snum;
}

int *get_prices(int n)
{ // This can be Excluded>>>>>>
    int *prices = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        FILE *fp;
        fp = fopen("tablets_dataset.txt", "r");
        while (!feof(fp))
        {
            char ch[100];
            int pric;
            fscanf(fp, "%s", ch);
            fscanf(fp, "%d", &pric);
            if (strstr(ch, tab_list[i]))
            {
                prices[i] = pric;
                // printf("%d) %s\n",i,tab_list[i]);
                break;
            }
        }
        fclose(fp);
    }
    return prices;
}

/*void add_p_data() // add patient data from file to linked list
{
    fptr = fopen("curr_bill_no.txt", "r");
    fscanf(fptr, "%d", &bill_no);
    fclose(fptr);
    fptr = fopen("patient_details.txt", "r");

    head = (struct patient *)malloc(sizeof(struct patient));

    ptr = head;
    for (int i = 0; i < bill_no; i++)
    {
        char ch;
        new_p = (struct patient *)malloc(sizeof(struct patient));
        // fscanf(fptr, "%[^\n]s%d%d", patient.p_name, &patient.p_age, &patient.p_bill_no);
        fscanf(fptr, "%[^\t]s", new_p->p_name);

        fscanf(fptr, "%d", &new_p->p_age);

        fscanf(fptr, "%d", &new_p->p_bill_no);
        fscanf(fptr, "%c", &new_p->gender);

        patient.next = new_p;
        ptr = new_p;
        patient.next = NULL;
    }
    printf("Old Data added\n");
    printf("04\n");
    fclose(fptr);
}
*/

void add_p() // To add a new patient details
{

    // if (head == NULL)
    // {
    //     head = (struct patient *)malloc(sizeof(struct patient));
    //     ptr = head;
    // }
    // else
    // {
    //     new_p = (struct patient *)malloc(sizeof(struct patient));
    //     patient.next = new_p;
    //     ptr = new_p;
    // }
    fflush(stdin);
    printf("\nEnter Patient Details:-\n\nShort Name: ");
    scanf("%[^\n]s", patient_add.p_name);
    printf("Age: ");
    scanf("%d", &patient_add.p_age);
    fflush(stdin);
    printf("Gender(M/F): ");
    scanf("%c", &patient_add.gender);
    fflush(stdin);
    bill_no++;
    patient_add.p_bill_no = bill_no;
    // patient_add.next = NULL;

    // fptr = fopen("patient_add_details.txt", "a");

    fptr = fopen("curr_bill_no.txt", "w");
    fprintf(fptr, "%d", bill_no);
    fclose(fptr);
    fptr = fopen("history.txt", "a");
    fprintf(fptr, "%s\t%d\t%d\t%c\n", patient_add.p_name, patient_add.p_age, patient_add.p_bill_no, patient_add.gender);
    fclose(fptr);
}
void print_bill_head() // prints bill head only
{
    char ch;
    fptr = fopen("bill.txt", "r");
    while (ch != EOF)
    {
        printf("\x1b[1;34m");
        ch = fgetc(fptr);
        if (ch == 63)
        {
            printf("\r|");
            printf("\x1b[1;31m");
            printf("Date:\x1b[22;34m %s", __DATE__);
            printf("\x1b[1;34m");
            continue;
        }
        if (ch == 126)
        {
            printf("\r|");
            printf("\x1b[1;31m");
            printf("Bill No.:\x1b[22;34m %d", patient_add.p_bill_no);
            printf("\x1b[1;34m");
            continue;
        }
        if (ch == 38)
        {
            printf("\r|");
            printf("\x1b[1;31m");
            int len = strlen(patient_add.p_name);
            printf("Name:\x1b[22;34m %s", patient_add.p_name);
            printf("\x1b[1;34m");
            for (int i = 0; i < (26 - len - 5); i++)
                printf(" ");
            continue;
        }
        if (ch == 35)
        {
            printf("\r|");
            printf("\x1b[1;31m");
            printf("Gender:\x1b[22;34m %c", patient_add.gender);
            printf("\x1b[1;34m");
            continue;
        }
        if (ch == 36)
        {
            printf("\x1b[1;31m");
            printf("BRANCH:\x1b[22;34m SRM UNIVERSITY");
            printf("\x1b[1;34m");
            continue;
        }
        if (ch == 94)
        {
            printf("\x1b[1;31m");
            printf("Address:\x1b[22;34m 123/45 G-floor");
            printf("\x1b[1;34m");
            continue;
        }
        if (ch == 33)
        {
            printf("\x1b[1;31m");
            printf("Tel No.:\x1b[22;34m 080-3266611");
            printf("\x1b[1;34m");
            continue;
        }
        if (ch == 96)
        {
            printf("\x1b[1;31m");
            printf("GSTIN:\x1b[22;34m 46KPDKA0328S2P1");
            printf("\x1b[1;34m");
            continue;
        }
        if (ch == 64)
        {
            printf("\r|");
            printf("\x1b[1;31m");
            printf("Age:\x1b[22;34m %d", patient_add.p_age);
            printf("\x1b[1;34m");
            continue;
        }
        if (ch == 42)
        {
            printf("\x1b[1;31m");
            printf("ABHI PHARMACY");
            printf("\x1b[1;34m");
            continue;
        }
        printf("%c", ch);
    }
    fclose(fptr);
    printf("\x1b[1;0m");
}

void print_bill_body(int prices[], int tab_ct)
{
    if (strlen(tab_list[0]) == 0)
    {
        return;
    }
    add_p();
    print_bill_head();
    float cgst = 0, sgst = 0, discount = 0, net_total = 0, tot_tax = 0;
    float taxable[tab_ct], tot_amt[tab_ct];
    srand(time(0));
    for (int i = 0; i < tab_ct; i++)
    {
        printf("\n\x1b[1;34m|\x1b[22;37m   %d", i + 1);
        printf("         ");
        int k = 0;
        for (int j = 0; j < 31; j++)
        {
            if (k == 0)
            {
                if (tab_list[i][j] == '\0')
                {
                    printf(" ");
                    k = 1;
                }
                printf("%c", tab_list[i][j]);
            }
            else
            {
                printf(" ");
            }
        }
        taxable[i] = tab_QTY[i] * (prices[i] / 10.0) * 0.15;
        tot_amt[i] = (tab_QTY[i] * (prices[i] / 10.0)) + taxable[i];

        cgst += (tot_amt[i] * 5) / 100;
        sgst += (tot_amt[i] * 5) / 100;
        tot_tax += cgst + sgst + taxable[i];
        discount += tot_amt[i] * 0.15;
        net_total += tot_amt[i] - discount;

        if (tab_QTY[i] < 9)
            printf("   0%d", tab_QTY[i]);
        else
            printf("   %d", tab_QTY[i]);
        int mfg_mth, exp_mth, mfg_yr, exp_yr;

        mfg_mth = (rand() % 10 + 1);
        mfg_yr = 23;
        exp_mth = mfg_mth + (rand() % 2 + 1);
        exp_yr = mfg_yr + (rand() % 3 + 1);
        if (mfg_mth < 10)
            printf("      0%d/%d", mfg_mth, mfg_yr);
        else
            printf("      %d/%d", mfg_mth, mfg_yr);
        if (exp_mth < 10)
            printf("      0%d/%d", exp_mth, exp_yr);
        else
            printf("      %d/%d", exp_mth, exp_yr);
        printf("      %d", prices[i]);
        if (prices[i] < 10000)
        {
            if (prices[i] < 1000)
            {

                if (prices[i] < 100)
                    printf("  ");
                else
                    printf(" ");
            }
        }

        if (prices[i] > 9999)
        {
            printf("     %.2f", taxable[i]);
        }
        else
            printf("      %.2f", taxable[i]);

        if (taxable[i] < 100.00)
        {
            if (taxable[i] < 10.00)
                printf("  ");
            else
                printf(" ");
        }

        printf("        %.2f", tot_amt[i]);
        if (tot_amt[i] < 10.00)
            printf("      \x1b[1;34m|\x1b[22;0m");
        else if (tot_amt[i] < 100.00)
            printf("     \x1b[1;34m|\x1b[22;0m");
        else if (tot_amt[i] < 1000.00)
            printf("    \x1b[1;34m|\x1b[22;0m");
        else
            printf("   \x1b[1;34m|\x1b[22;0m");
    }

    printf("\n\x1b[1;34m|---------------------------------------------------------------------------------------------------------------|\n");
    printf("|                                                                                       | CGST %%:  \x1b[22;37m %.2f\x1b[1;34m", cgst);
    if (cgst < 1000.00)
    {
        if (cgst < 100.00)
        {
            if (cgst < 10.00)
            {
                printf("        ");
                printf("|\n");
            }
            else
            {
                printf("       ");
                printf("|\n");
            }
        }
        else
        {
            printf("      ");
            printf("|\n");
        }
    }

    printf("|              \x1b[22;31m NOTE:\x1b[22;37m Goods once sold cannot be TAKEN BACK or EXCHANGED!               \x1b[1;34m | SGST %%:  \x1b[22;37m %.2f\x1b[1;34m", sgst);
    if (sgst < 1000.00)
    {
        if (sgst < 100.00)
        {
            if (sgst < 10.00)
            {
                printf("        ");
                printf("|\n");
            }
            else
            {
                printf("       ");
                printf("|\n");
            }
        }
        else
        {
            printf("      ");
            printf("|\n");
        }
    }
    printf("|                                                                                      \x1b[1;34m | TOT TAX %%:\x1b[22;37m%.2f\x1b[1;34m", tot_tax);
    if (tot_tax < 10000.00)
    {
        if (tot_tax < 1000.00)
        {
            if (tot_tax < 100.00)
            {
                if (tot_tax < 10.00)
                {
                    printf("        ");
                    printf("|\n");
                }
                else
                {
                    printf("       ");
                    printf("|\n");
                }
            }
            else
            {
                printf("      ");
                printf("|\n");
            }
        }
        else
        {
            printf("     ");
            printf("|\n");
        }
    }

    printf("|---------------------------------------------------------------------------------------|                       |\n");
    printf("|---------------------------------------------------------------------------------------|-----------------------|\n");
    printf("|             \x1b[22;31m CAUTION:\x1b[22;37m Kindly make sure to take admintered doses only!!!              \x1b[1;34m | DISCOUNT:\x1b[22;37m  %.2f\x1b[1;34m", discount);
    if (discount < 1000.00)
    {
        if (discount < 100.00)
        {
            if (discount < 10.00)
            {
                printf("       ");
                printf("|\n");
            }
            else
            {
                printf("      ");
                printf("|\n");
            }
        }
        else
        {
            printf("     ");
            printf("|\n");
        }
    }

    printf("|                                                                                       |-----------------------|\n");
    printf("|---------------------------------------------------------------------------------------| NET TOTAL:\x1b[22;37mRs.%.2f/-\x1b[1;34m", net_total);
    sales += net_total;
    if (net_total < 10000.00)
    {
        if (net_total < 1000.00)
        {
            if (net_total < 100.00)
            {
                if (net_total < 10.00)
                {
                    printf("   ");
                    printf("|\n");
                }
                else
                {
                    printf("  ");
                    printf("|\n");
                }
            }
            else
            {
                printf(" ");
                printf("|\n");
            }
        }
        else
        {
            printf("|\n");
        }
    }
    printf("|                 \x1b[22;35mWishing for a Healthy and Happy Life \x1b[22;37m~\x1b[1;33m ABHI PHARMACY \x1b[1;34m                 |                       |\n");
    printf("|_______________________________________________________________________________________|_______________________|\x1b[22;0m\n");

    printf("\e[?25l");
    printf("\nPress Any KEY to Continue...");
    getch();
    fflush(stdin);
    system("cls");
    search_sym_med();
}
void search_sym_med()
{
    int choice;
start:
    print_logo(1);
    printf("\e[?25l");
    printf("\n\t\t\t\t\t\t");
    for (int i = 0; i < 34; i++)
    {
        printf("\xdb");
    }
    printf("\n");
    printf("\t\t\t\t\t\t\xdb\xdb                              \xdb\xdb\n");
    printf("\t\t\t\t\t\t\xdb\xdb    1. SEARCH BY SYMPTOMS     \xdb\xdb\n");
    printf("\t\t\t\t\t\t\xdb\xdb                              \xdb\xdb\n");
    printf("\t\t\t\t\t\t\xdb\xdb    2. SEARCH BY MEDICINES    \xdb\xdb\n");
    printf("\t\t\t\t\t\t\xdb\xdb                              \xdb\xdb\n");
    printf("\t\t\t\t\t\t\xdb\xdb    3. UPDATE STOCK           \xdb\xdb\n");
    printf("\t\t\t\t\t\t\xdb\xdb                              \xdb\xdb\n");
    printf("\t\t\t\t\t\t\xdb\xdb    4. CHECK SALES            \xdb\xdb\n");
    printf("\t\t\t\t\t\t\xdb\xdb                              \xdb\xdb\n");
    printf("\t\t\t\t\t\t\xdb\xdb    5. LOGOUT                 \xdb\xdb\n");
    printf("\t\t\t\t\t\t\xdb\xdb                              \xdb\xdb\n");
    printf("\t\t\t\t\t\t");
    for (int i = 0; i < 34; i++)
    {
        printf("\xdb");
    }
    printf("\n");
    printf("\n\n      > ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        int sym_ct; // selected symptoms count
        sym_ct = get_symptoms();
        int *prices;
        predict_medicine(sym_ct);
        int med_ct = generate_medicine(sym_ct);
        if (med_ct == 0)
        {
            printf("Press any key to continue...");
            getch();
            goto start;
        }
        prices = get_prices(med_ct);
        printf("\n");
        // for(int i=0;i<med_ct;i++){
        //    printf("%s   {%d}/pre 10\n",tab_list[i],prices[i]);
        // }

        // bill(prices, med_ct);
        print_bill_body(prices, med_ct);
    }
    else if (choice == 2)
    {
        int tab_ct = get_tablets();
        if (tab_ct == 0)
        {
            printf("Press any key to continue...");
            getch();
            goto start;
        }
        int *prices;
        prices = get_prices(tab_ct);
        // for(int i=0;i<tab_ct;i++){
        //     printf("%s   {%d}/per 10\n",tab_list[i],prices[i]);
        // }

        // bill(prices, tab_ct);
        print_bill_body(prices, tab_ct);
    }
    else if (choice == 3)
    {
        struct tablet tab;
        system("cls");
        print_logo(1);
        printf("\n\nEnter the tablet to be added: ");
        scanf("%s", tab.name);
        printf("Price: ");
        scanf("%f", &tab.price);
        printf("QTY: ");
        scanf("%d", &tab.quantity);
        printf("Expiry (MM/YY): ");
        scanf("%d/%d", &tab.dd.mm, &tab.dd.yy);
        FILE *fp = fopen("tablets_dataset.txt", "a");
        fprintf(fp, "%s %.0f", tab.name, tab.price);
        fclose(fp);
        goto start;
    }
    else if (choice == 4)
    {
        print_logo(1);
        printf("\n\n");
        FILE *fpp = fopen("history.txt", "r");
        // if(fp==NULL) printf("Error\n");
        char arr[500];
        // printf("Hello\n");
        while (!feof(fpp))
        {
            // printf("Hello\n");
            fgets(arr, 500, fpp);
            // printf("Hello\n");
            printf("%s\n", arr);
        }
        fclose(fpp);
        printf("\n\npress any key to continue...");
        getch();
        fflush(stdin);
        system("cls");
        goto start;
    }
    else if (choice == 5)
    {
        system("cls");
        print_logo(1);
        time_t curtime;
        time(&curtime);
        printf("\n\n\n\t\t\t\t\t\tLOGOUT SUCCESSFUL\n\n");
        printf("\t\t\t\t\t\tHAVE A SUCCESSFUL DAY!!!\n\n\n");
        fptr = fopen("history.txt", "a"); // to note entry of user in the history
        fprintf(fptr, "Sales: %.2f", sales);

        fprintf(fptr, "\nLOG-OUT: %s\n", ctime(&curtime));
        fclose(fptr);
        return 0;
        login_page();
    }
    else
    {
        printf("Wrong choice!!\n");
        printf("Press any key to continue...");
        char c = getch();
        fflush(stdin);
        system("cls");
        goto start;
    }
    printf("\e[?25h");
}

int main()
{
    fptr = fopen("curr_bill_no.txt", "r");
    fscanf(fptr, "%d", &bill_no);
    fclose(fptr);
    login_page();
}
