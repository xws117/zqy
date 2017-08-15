# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
# include <string.h>
# include <algorithm>
using namespace std;

int num;//���ص�����

int inp_total_order[100];//ÿ�����صĶ���������
int inp_car_count[100];//ÿ��������Ҫ��car������
double car_volume = 6; // ÿһ��car������
int car_total =0; //����Ҫ��car���ܵ�����
int car_cnt = 5;  //��������
int car_get_time[100]; //�����������վ��·�̵�ʱ��
int chuning[100];  //��������  ÿ�������ĳ���ʱ��
int dnas[1000][1000]; // ���е�dna
struct car_arrive{
    int id ;
    int time;
};
struct car{
    int id;
    int val;
};
int cmp ( const void *p1 , const void *p2 ){
    struct car *c=(car*)p1;
    struct car *c1=(car*)p2;
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
double value(int * dna,int cnt){
    for(int i=0;i<cnt;i++){
        printf("aqwer %d",dna[i]);
    }
    return 0;
}
int chuning_check(int *dna,int cnt,int car_cnt){  // �������
    int mark =0;//0 �����ɹ� 1 ����ʧ��
    //int timestamp[1000];
    int car_time_cnt[car_cnt];//��ÿһ������ʱ��ļ�¼
    // ����ʱ���ʼ��
    for(int i=0;i<car_cnt;i++){
        car_time_cnt[i]=0;
    }
    car_arrive arrive[1000];
    memset(arrive,0,sizeof(1000));
    for(int i=0;i<cnt;i++){
        arrive[i].id = dna[i];
    }
    int start_time =0;
    for(int i=0;i<cnt;i++){
        int tmp = get_min(car_time_cnt,car_cnt);
        arrive[i].id = dna[i];
        arrive[i].time = car_get_time[dna[i]];
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
    return mark;
}
void to_swap(int i,int one ,int two){
    int tmp = dnas[i][one];
    dnas[i][one] = dnas[i][two];
    dnas[i][two] = tmp;


}
void exchange(int cnt){
    srand((unsigned)time(NULL));
    for(int i=1;i<1000;i++){
        for(int k=0;k<cnt;k++){
            dnas[i][k] = dnas[i-1][k];
        }
        for(int k=0;k<5;k++){
            int tmp_one = rand()%cnt;
            int tmp_two = rand()%cnt;
            to_swap(i,tmp_one,tmp_two);
        }
    }
}
int main(){
    scanf("%d",&num);
    int dna[1000];
    //begin ������
    for(int i=0;i<num;i++){
        car_get_time[i] = 10+10*i;
    }
    for(int i=0;i<num;i++){
        inp_total_order[i]=50;
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
            dna[cnt] = i;
            cnt++;
        }
    }
    //test of dna
    for(int i=0;i<cnt;i++){
        printf("%d ",dna[i]);
    }
    double ans = value(dna,cnt);
    //time_t timep;

    //time(&timep); /*��ȡtime_t���͵ĵ�ǰʱ��*/
    /*��gmtime��time_t���͵�ʱ��ת��Ϊstruct tm���͵�ʱ�䣬��û�о���ʱ��ת����UTCʱ��
      Ȼ������asctimeת��Ϊ���ǳ����ĸ�ʽ Fri Jan 11 17:25:24 2008
    */
    //printf("%s", asctime(localtime(&timep)));
    //printf("%d",timep);
    //�����ݿ��ȡһ��ʱ���
    for(int i=0;i<)
    for(int i=0;i<500;i++){
        for(int j=0;j<10;j++){
            exchange(cnt);  //Ⱦɫ�彻��
            for(int i=0;i<100;i++){
                int mark = chuning_check(dnas[i],cnt,car_cnt);  //���Ⱦɫ�彻���Ժ�����е�Ⱦɫ����г������
                if(mark==1){
                   check_fales_deal(i)//��ʧ�ܵĽ��б��
                }else{   //�����еĺϸ����ɫ�����value����
                    int val = value(i);
                    //�ҳ����ֵ���б��
                    //�����е�ʧ�ܵ�Ⱦɫ���������dna�ı�д�������Ž�������Ž�ı��ָ�ֵ����
                }
            }
        }
    }
    return 0;
}
