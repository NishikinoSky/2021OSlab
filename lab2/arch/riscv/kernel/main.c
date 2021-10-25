typedef unsigned long long uint64_t;
extern puts();
extern init();
extern get_cycles();
extern uint64_t sbi_call(uint64_t sbi_type, uint64_t arg0, uint64_t arg1, uint64_t arg2);


int main(){
    int a=0;
    init();
    while(1){
		if(a++>10000){
		    a=0;
		}
	}
    return 0;
}