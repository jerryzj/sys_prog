#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/random.h>

const int64_t MAX_ITER = 1e7;
const int64_t STRIDE   = 1e3;

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jerry ZJ");
MODULE_DESCRIPTION("A simple program to evaluate overhead of FP inst.");
MODULE_VERSION("0.1");

static int __init fp_eval_init (void) {
    __kernel_time64_t start_time, end_time;
    int x = 0;
    int y = 0;
#ifdef INT
    int32_t a, b, c;
#elif FP
    float a, b, c;
#endif
    start_time = 0;
    end_time = 0;
    
    while (x ==0 || y ==0) {
        get_random_bytes(&x, sizeof(x));
        get_random_bytes(&y, sizeof(y));
    }
    
#ifdef INT            
    a = x;
    b = y;  
#elif FP                
    a = (float) x + (float) 1.0 / y;
    b = (float) x + (float) 1.0 / y;
#endif

    for(int i = 0; i < MAX_ITER; i += STRIDE) {
        start_time = ktime_get_ns();
        for(int j = 0; j < i; ++j){
            c = a * b;
        }
        end_time = ktime_get_ns();
        printk(KERN_DEBUG "%d %lld", i, end_time - start_time);
    }
    return 0;
}

static void __exit fp_eval_exit(void){}

module_init(fp_eval_init);
module_exit(fp_eval_exit);