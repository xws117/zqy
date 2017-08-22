# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
# include <string.h>
# include <algorithm>
//# include <winsock2.h>
//# include <mysql.h>
# include <iostream>
using namespace std;

#define HOST "localhost"
#define USERNAME "root"
#define PASSWORD "123456"
#define DATABASE "test"



int num;//���ص�����

int inp_total_order[100];//ÿ�����صĶ���������
int inp_car_count[100];//ÿ��������Ҫ��car������
double car_volume = 6; // ÿһ��car������
int car_total =0; //����Ҫ��car���ܵ�����
int car_cnt = 5;  //��������
int car_get_time[100]; //�����������վ��·�̵�ʱ��
int chuning[100];  //��������  ÿ�������ĳ���ʱ��

struct DNAS{
    int dna[1000];
    int val;
}dnas[1000]; // ���е�dna
int chengfa[100]; //�ͷ�����
struct car_arrive{
    int id ;
    int time;
};
car_arrive arrive[1000];
struct car{
    int id;
    int val;
};
int cmp ( const void *p1 , const void *p2 ){
    struct car *c=(car*)p1;
    struct car *c1=(car*)p2;
    return c->val-c1->val;
}
int dna_cmp ( const void *p1 , const void *p2 ){
    struct DNAS *c=(DNAS*)p1;
    struct DNAS *c1=(DNAS*)p2;
    return c->val-c1->val;
}
int get_min(int * car_time,int car_cnt){
    car E[car_cnt];
    for(int i=0;i<car_cnt;i++){
        E[i].id = i;
        E[i].val = car_time[i];
    }
    qsort(E,car_cnt,sizeof(E[0]),cmp);
    return E[0].id;
}
int chuning_check(int *dna,int cnt,int car_cnt){  // �������
    //memset(arrive,0,sizeof(arrive));
    printf("\n");
    int mark =0;//0 ����ɹ� 1 ����ʧ��
    //int timestamp[1000];
    int car_time_cnt[car_cnt];//��ÿһ������ʱ��ļ�¼
    // ����ʱ���ʼ��
    for(int i=0;i<car_cnt;i++){
        car_time_cnt[i]=0;
    }
    memset(arrive,0,sizeof(1000));
    for(int i=0;i<cnt;i++){
        arrive[i].id = dna[i];
    }
    int start_time =0;
    for(int i=0;i<cnt;i++){
        int tmp = get_min(car_time_cnt,car_cnt);
        arrive[i].id = dna[i];
        //printf("dna[i] == %d ",dna[i]);
        arrive[i].time = car_get_time[dna[i]]+car_time_cnt[tmp];
        printf("arrive time =  %d ",arrive[i].time);
        car_time_cnt[tmp]+=car_get_time[dna[i]]*2;

    }
    for(int i=0;i<num;i++){ //��һ��ѭ��  ��ÿ������
        int time_tmp = -1;
        for(int j=0;j<cnt;j++){  //����dna  ���������ļ��
            if(arrive[j].id==i){
                if(time_tmp==-1){
                    time_tmp = arrive[j].time;
                }else{
                    if((arrive[j].time-time_tmp)>chuning[i]){
                        mark = 1;
                        break;
                    }else{
                        time_tmp = arrive[j].time;
                    }
                }
            }
        }

    }
    /*printf("\n");
    for(int i=0;i<cnt;i++){
        printf("%d ",arrive[i].time);
    }
    printf("\n");*/
    return mark;
}
void to_swap(int i,int one ,int two){
    int tmp = dnas[i].dna[one];
    dnas[i].dna[one] = dnas[i].dna[two];
    dnas[i].dna[two] = tmp;


}
void exchange(int cnt){
    srand((unsigned)time(NULL));
    for(int i=1;i<1000;i++){
        for(int k=0;k<cnt;k++){
            dnas[i].dna[k] = dnas[i-1].dna[k];
        }
        for(int k=0;k<3;k++){
            int tmp_one = rand()%cnt;
            int tmp_two = rand()%cnt;
            //printf("tmp_one == %d tmp_two == %d\n",tmp_one,tmp_two);
            to_swap(i,tmp_one,tmp_two);
        }
    }
}
void check_fales_deal(int  a){

}
int value(int car,int cnt){
    int ans =0;
    //printf("car_cnt==%d\n",car_cnt);
    for(int i=0;i<car_cnt;i++){
        int mark = -1;
        for(int k=0;k<cnt;k++){
            if(mark==-1&&dnas[car].dna[k]==i){
                mark = arrive[k].time;
            }else if(mark!=-1&&dnas[car].dna[k]==i){
                ans += (arrive[k].time-mark)*chengfa[i];
                mark = arrive[k].time;
                //printf("arrive time = %d",mark);
            }
        }
    }
    return ans;
}
int main(){
    //printf("begin");
    //char *query;
    //query="select * from student";
    //query_sql();


    printf("�����빤�ص����������س�����\n");
    scanf("%d",&num);
    //����ÿ�����ĳͷ�����
    for(int i=0;i<car_cnt;i++){
        chengfa[i] = i*10;
    }
    //begin ������
    for(int i=0;i<num;i++){
        chengfa[i] = i;
    }
    for(int i=0;i<num;i++){
        car_get_time[i] = 10+10*i;
    }
    for(int i=0;i<num;i++){
        inp_total_order[i]=50;
    }
    for(int i=0;i<num;i++){
        chuning[i]=50+i*10;
    }
    for(int i=0;i<num;i++){
        //printf("%lf",inp_total_order[i]/car_volume);
        inp_car_count[i]=(int)ceil(inp_total_order[i]/car_volume);
        //printf("%d\n",inp_car_count[i]);
        car_total += inp_car_count[i];
    }
    //end of ������
    int cnt=0;
    for(int i=0;i<num;i++){
        int tmp_cnt = inp_car_count[i];
        for(int j=0;j<tmp_cnt;j++){
            dnas[0].dna[cnt] = i;
            cnt++;
        }
    }
    //test of dna
    for(int i=0;i<cnt;i++){
        //printf("%d ",dnas[0].dna[i]);
    }


    //��dnas��ʼ��
    for(int i=0;i<1000;i++){
        dnas[i].val = 99999999;
    }

    //double ans = value(dna,cnt);
    //time_t timep;

    //time(&timep); /*��ȡtime_t���͵ĵ�ǰʱ��*/
    /*��gmtime��time_t���͵�ʱ��ת��Ϊstruct tm���͵�ʱ�䣬��û�о���ʱ��ת����UTCʱ��
      Ȼ������asctimeת��Ϊ���ǳ����ĸ�ʽ Fri Jan 11 17:25:24 2008
    */
    //printf("%s", asctime(localtime(&timep)));
    //printf("%d",timep);
    //�����ݿ��ȡһ��ʱ���
    for(int k=0;k<5;k++){
        //printf("���õ��ĳ���Ϊ ===  %d\n",cnt);
        printf("��%d�ε���\n",k);
        exchange(cnt);  //Ⱦɫ�彻��
        for(int i=0;i<5;i++){
            for(int j=0;j<cnt;j++){
                printf("%d ",dnas[i].dna[j]);
            }
            printf("\n");
            printf("��������  ");
            int mark = chuning_check(dnas[i].dna,cnt,car_cnt);  //���Ⱦɫ�彻���Ժ�����е�Ⱦɫ����г������
            if(mark==1){
               printf("   δͨ��\n");
               check_fales_deal(i);//��ʧ�ܵĽ��б��
               dnas[i].val = 99999999;
            }else{   //�����еĺϸ����ɫ�����value����
                printf("   ͨ��\n");
                int val = value(i,cnt);
                dnas[i].val = val;
                printf("val == %d \n",val);
                //�ҳ����ֵ���б��
                //�����е�ʧ�ܵ�Ⱦɫ���������dna�ı�д�������Ž�������Ž�ı��ָ�ֵ����
            }
        }
        qsort(dnas,1000,sizeof(dnas[0]),dna_cmp);
        printf("��%d�ε�������\n",k);
        for(int i=0;i<cnt;i++){
            printf("%d ",dnas[0].dna[i]);
        }
        printf("����valueֵΪ===%d\n",dnas[0].val);
    }
    return 0;
}

