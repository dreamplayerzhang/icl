#include <ICLUtils/Semaphore.h>
#include <semaphore.h>
#include <ICLUtils/Macros.h>

namespace icl{
  

  class SemaphoreImpl{
  public:
    inline SemaphoreImpl(int n):n(n){
      ICLASSERT_RETURN(n>0);
      sem_init(&s,0,(unsigned int)n);
    }
    inline ~SemaphoreImpl(){
      sem_destroy(&s);
    }
    inline void inc(int n=1){
      for(int i=0;i<n;i++){
        sem_post(&s);
      }
    }
    inline void dec(int n=1){
      for(int i=0;i<n;i++){
        sem_wait(&s);
      }
    }
    inline int getValue(){
      int val = 0;
      sem_getvalue(&s,&val);
      return val;
    }
    inline int getMaxValue(){
      return n;
    }

    inline bool tryAcquire(){
      int ret = sem_trywait(&s);
      return ret == 0;
    }
    inline bool tryRelease(){
      int ret = sem_post(&s);
      return ret == 0;
    }
  private:
    sem_t s;
    int n;
  };
  
  void SemaphoreImplDelOp::delete_func(SemaphoreImpl *impl){
    ICL_DELETE(impl);
  }
  
  
  Semaphore::Semaphore(int n):
    ShallowCopyable<SemaphoreImpl,SemaphoreImplDelOp>(new SemaphoreImpl(n)){
    
  }
  
  void Semaphore::operator++(int dummy){
    (void)dummy;
    impl->inc(1);
  }
  void Semaphore::operator--(int dummy){
    (void)dummy;
    impl->dec(1);
  }
  void Semaphore::operator+=(int val){
    impl->inc(val);
  }
  void Semaphore::operator-=(int val){
    impl->dec(val);
  }
  bool Semaphore::tryAcquire(){
    return impl->tryAcquire();
  }
 
  bool Semaphore::tryRelease(){
    return impl->tryRelease();
  }
  
  int Semaphore::getValue(){
    return impl->getValue();
  } 
  int Semaphore::getMaxValue(){
    return impl->getMaxValue();
  }
}

