# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
# include <string.h>
# include <algorithm>
using namespace std;

int num;//工地的数量

int inp_total_order[100];//每个工地的订单的数量
int inp_car_count[100];//每个工地需要的car的数量
double car_volume = 6; // 每一个car的容量
int car_total =0; //所需要的car的总的数量
int car_cnt = 5;  //车的数量
int car_get_time[100]; //车辆到达搅拌站的路程的时间
int chuning[100];  //限制条件  每个工厂的初凝时间
int dnas[1000][1000]; // 所有的dna
int chengfa[100];  //惩罚因子
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
int chuning_check(int *dna,int cnt,int car_cnt){  // 初凝检测
    int mark =0;//0 代表成功 1 代表失败
    //int timestamp[1000];
    int car_time_cnt[car_cnt];//对每一辆车做时间的记录
    // 车辆时间初始化
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
    for(int i=0;i<num;i++){ //第一层循环  对每个工地
        int time_tmp = -1;
        for(int j=0;j<cnt;j++){  //便利dna  找两辆车的间隔
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
void check_fales_deal(int  a){

}
double value(int i){

    return 0;
}
int main(){
    scanf("%d",&num);
    int dna[1000];
    //begin 假数据
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
        //printf("%lf",inp_total_order[i]/car_volume);
        inp_car_count[i]=(int)ceil(inp_total_order[i]/car_volume);
        //printf("%d\n",inp_car_count[i]);
        car_total += inp_car_count[i];
    }
    //end of 假数据
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
    //double ans = value(dna,cnt);
    //time_t timep;

    //time(&timep); /*获取time_t类型的当前时间*/
    /*用gmtime将time_t类型的时间转换为struct tm类型的时间，按没有经过时区转换的UTC时间
      然后再用asctime转换为我们常见的格式 Fri Jan 11 17:25:24 2008
    */
    //printf("%s", asctime(localtime(&timep)));
    //printf("%d",timep);
    //从数据库读取一个时间戳
    for(int i=0;i<500;i++){
        for(int j=0;j<10;j++){
            exchange(cnt);  //染色体交换
            for(int i=0;i<100;i++){
                int mark = chuning_check(dnas[i],cnt,car_cnt);  //完成染色体交换以后对所有的染色体进行初凝检测
                if(mark==1){
                   check_fales_deal(i);//对失败的进行标记
                }else{   //对所有的合格的颜色体进行value计算
                    int val = value(i);
                    //找出最大值进行标记
                    //对所有的失败的染色体进行重新dna的编写，把最优解或者最优解的变种赋值给他
                }
            }
        }
    }
    return 0;
}