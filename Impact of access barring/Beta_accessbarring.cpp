#include <bits/stdc++.h>
#include <iostream>
#include <random>
#include <vector>
#include <fstream>

namespace sftrabbit {

  template <typename RealType = double>
  class beta_distribution
  {
    public:
      typedef RealType result_type;

      class param_type
      {
        public:
          typedef beta_distribution distribution_type;

          explicit param_type(RealType a = 2.0, RealType b = 2.0)
            : a_param(a), b_param(b) { }

          RealType a() const { return a_param; }
          RealType b() const { return b_param; }

          bool operator==(const param_type& other) const
          {
            return (a_param == other.a_param &&
                    b_param == other.b_param);
          }

          bool operator!=(const param_type& other) const
          {
            return !(*this == other);
          }

        private:
          RealType a_param, b_param;
      };

      explicit beta_distribution(RealType a = 2.0, RealType b = 2.0)
        : a_gamma(a), b_gamma(b) { }
      explicit beta_distribution(const param_type& param)
        : a_gamma(param.a()), b_gamma(param.b()) { }

      void reset() { }

      param_type param() const
      {
        return param_type(a(), b());
      }

      void param(const param_type& param)
      {
        a_gamma = gamma_dist_type(param.a());
        b_gamma = gamma_dist_type(param.b());
      }

      template <typename URNG>
      result_type operator()(URNG& engine)
      {
        return generate(engine, a_gamma, b_gamma);
      }

      template <typename URNG>
      result_type operator()(URNG& engine, const param_type& param)
      {
        gamma_dist_type a_param_gamma(param.a()),
                        b_param_gamma(param.b());
        return generate(engine, a_param_gamma, b_param_gamma); 
      }

      result_type min() const { return 0.0; }
      result_type max() const { return 1.0; }

      result_type a() const { return a_gamma.alpha(); }
      result_type b() const { return b_gamma.alpha(); }

      bool operator==(const beta_distribution<result_type>& other) const
      {
        return (param() == other.param() &&
                a_gamma == other.a_gamma &&
                b_gamma == other.b_gamma);
      }

      bool operator!=(const beta_distribution<result_type>& other) const
      {
        return !(*this == other);
      }

    private:
      typedef std::gamma_distribution<result_type> gamma_dist_type;

      gamma_dist_type a_gamma, b_gamma;

      template <typename URNG>
      result_type generate(URNG& engine,
        gamma_dist_type& x_gamma,
        gamma_dist_type& y_gamma)
      {
        result_type x = x_gamma(engine);
        return x / (x + y_gamma(engine));
      }
  };

  template <typename CharT, typename RealType>
  std::basic_ostream<CharT>& operator<<(std::basic_ostream<CharT>& os,
    const beta_distribution<RealType>& beta)
  {
    os << "~Beta(" << beta.a() << "," << beta.b() << ")";
    return os;
  }

  template <typename CharT, typename RealType>
  std::basic_istream<CharT>& operator>>(std::basic_istream<CharT>& is,
    beta_distribution<RealType>& beta)
  {
    std::string str;
    RealType a, b;
    if (std::getline(is, str, '(') && str == "~Beta" &&
        is >> a && is.get() == ',' && is >> b && is.get() == ')') {
      beta = beta_distribution<RealType>(a, b);
    } else {
      is.setstate(std::ios::failbit);
    }
    return is;
  }

}

using namespace std;

int main(){
	int arr[] = {1500};
	int size = sizeof(arr)/sizeof(arr[0]);
	int maxattempts[3] = {5,5,5};
	int globalAttempts = 10;
	int W[3] = {512,1024,2048}; 
	int T_b[3] = {80,160,640}; // in ms
	int T_ok[3] = {68,152,476}; //in ms
	int T_col[3] = {28,100,376}; // in ms
	int P[3] = {12,12,12};
	ofstream myfile;
	myfile.open ("Beta_accessprob11.txt");
	std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
	std::uniform_int_distribution<int>  distr(0,11);
    std::random_device                  rand_dev1;
    std::mt19937                        generator1(rand_dev1());
    std::uniform_int_distribution<int>  distr1(12,23);
    std::random_device                  rand_dev2;
    std::mt19937                        generator2(rand_dev2());
    std::uniform_int_distribution<int>  distr2(24,35);
    std::random_device                  rand_dev3;
    std::mt19937                        generator3(rand_dev3());
    std::uniform_int_distribution<int>  distr3(0,W[0]);
    std::random_device                  rand_dev4;
    std::mt19937                        generator4(rand_dev4());
    std::uniform_int_distribution<int>  distr4(0,W[1]);
    std::random_device                  rand_dev5;
    std::mt19937                        generator5(rand_dev5());
    std::uniform_int_distribution<int>  distr5(0,W[2]);
    std::random_device                  rand_dev6;
    std::mt19937                        generator6(rand_dev6());
    sftrabbit::beta_distribution<double> beta(3,4);
    std::random_device                  rand_dev7;
    std::mt19937                        generator7(rand_dev7());
    std::uniform_int_distribution<int>  distr7(0,100);
    
     double alpha[] = {0.5,0.7,0.9};
    int size1 = sizeof(alpha)/sizeof(alpha[0]);
    for(int al = 0;al<size1;al++){
      double alpha1 = alpha[al];
      myfile << alpha1 << "-------" << endl;
    for(int i=0;i<size;i++){
    double success[3] = {0};
    double success_overall = 0;
    double delay_overall = 0;
    double delay[3] = {0};
    double thr[3] = {0};
     int a=100;
 while(a-- > 0){
      int N = arr[i];
      cout << N << endl;
      int UE_CElevel[N];
      int initial_CElevel[N];
      int backoff[N];
    int delayperUE[N];
    double meandelay[3] = {0};
    int attempts[N];
    int ack[3] = {0};
    int drop[3] = {0};
    int ack_initial[3] = {0};
    int drop_initial[3] = {0};
    int slot = 8; //in ms
    int T_start = 8; //in ms
    int flag[N] = {0};
    int packet_arrival[N] = {0};
    int initial_arrival[N] = {0};
    int slots_CElevel[3] = {0};
    int s;
    for(int i=0;i<N;i++){
      if(i<N/3){
        UE_CElevel[i] = 0;
        initial_CElevel[i] = 0;
        attempts[i] = maxattempts[0];
      }
      else if(i< 2*N/3){
        UE_CElevel[i] = 1;
        initial_CElevel[i] = 1;
        attempts[i] = maxattempts[1];
      }
      else{
        UE_CElevel[i] = 2;
        initial_CElevel[i] = 2;
        attempts[i] = globalAttempts;
      }
      packet_arrival[i] = beta(generator6)*10000;
      initial_arrival[i] = packet_arrival[i];
      delayperUE[i] = 0;
      backoff[i] = 0;
    }
    int P_total = P[0]+P[1]+P[2];
      while(ack[0]+ack[1]+ack[2]+drop[0]+drop[1]+drop[2] < N){
        int flagSlot[P_total] = {0};
      vector<int> slotUE[P_total];
      for(int j=0;j<N;j++){
        double param = distr7(generator7);
        param = param/100;
        if(flag[j] == 0 && UE_CElevel[j] == 0 && (slot-T_start)%T_b[0] == 0 && packet_arrival[j] < slot && param < alpha1){
          if(packet_arrival[j] == initial_arrival[j]) initial_arrival[j] = slot;
          s = distr(generator);
          flagSlot[s]++;
          slotUE[s].push_back(j);
        }
        else if(flag[j] == 0 && UE_CElevel[j] == 0 && (slot-T_start)%T_b[0] == 0 && packet_arrival[j] < slot && param > alpha1){
          packet_arrival[j] += (0.7+0.5*distr7(generator7)/100)*16000;
        }

        if(flag[j] == 0 && UE_CElevel[j] == 1 && (slot-T_start)%T_b[1] && packet_arrival[j] < slot && param < alpha1){
          if(packet_arrival[j] == initial_arrival[j]) initial_arrival[j] = slot;
          s = distr1(generator);
          flagSlot[s]++;
          slotUE[s].push_back(j);
        }
        else if(flag[j] == 0 && UE_CElevel[j] == 1 && (slot-T_start)%T_b[1] && packet_arrival[j] < slot && param > alpha1){
          packet_arrival[j] += (0.7+0.5*distr7(generator7)/100)*16000;
        }

        if(flag[j] == 0 && UE_CElevel[j] == 2 && (slot-T_start)%T_b[2] == 0 && packet_arrival[j] < slot && param < alpha1){
          if(packet_arrival[j] == initial_arrival[j]) initial_arrival[j] = slot;
          s = distr2(generator);
          flagSlot[s]++;
          slotUE[s].push_back(j);
        }
        else if(flag[j] == 0 && UE_CElevel[j] == 2 && (slot-T_start)%T_b[2] == 0 && packet_arrival[j] < slot && param > alpha1){
          packet_arrival[j] += (0.7+0.5*distr7(generator7)/100)*16000;
        }
      }

      for(int j=0;j<P_total;j++){
        if(flagSlot[j] == 1){
          int UE = slotUE[j][0];
          ack[UE_CElevel[UE]]++;
          //cout << ack[0] << "\n";
          ack_initial[initial_CElevel[UE]]++;
          flag[UE] = 1;
          packet_arrival[UE] = slot+T_ok[UE_CElevel[UE]];
          meandelay[initial_CElevel[UE]] += ((double)packet_arrival[UE]-initial_arrival[UE])/1000; 
        }
        else if(flagSlot[j] > 1){
          for(int k=0;k<slotUE[j].size();k++){
            int UE = slotUE[j][k];
            attempts[UE]--;
            int CElevel = UE_CElevel[UE];
            packet_arrival[UE] = slot+T_col[CElevel];
             if(attempts[UE] == 0 && CElevel < 2){
                     if(CElevel == 0){
                        attempts[UE] = max(0,min(maxattempts[CElevel+1],globalAttempts- maxattempts[CElevel]));
                      }
                      else{
                        attempts[UE] = max(0,min(maxattempts[CElevel+1],globalAttempts- maxattempts[CElevel]-maxattempts[CElevel-1]));
                      }
              
                      if(attempts[UE] == 0){
                        drop[UE_CElevel[UE]]++;
                        drop_initial[initial_CElevel[UE]]++;
                        flag[UE] = 2;
                      }
                      else{
                        UE_CElevel[UE] = CElevel+1;
                        CElevel = CElevel+1;
                      }
            }
            else if(attempts[UE] != 0){
              if(CElevel == 0){
              //packet_arrival[UE] = T_col[CElevel];
                packet_arrival[UE] += distr3(generator3); 
              //delayperUE[UE] = (delayperUE[UE] + (double)backoff[UE])*T_b[0];
              }
              else if(CElevel == 1){
              //packet_arrival[UE] += T_col[CElevel];
                packet_arrival[UE] += distr4(generator4); 
              //delayperUE[UE] = (delayperUE[UE] + (double)backoff[UE])*T_b[1];
              }
              else if(CElevel == 2){
                //packet_arrival[UE] += T_col[CElevel];
                packet_arrival[UE] += distr5(generator5); 
                //delayperUE[UE] = (delayperUE[UE] + (double)backoff[UE])*T_b[2];
              }
            }

            if(attempts[UE] == 0 && CElevel == 2){
              drop[UE_CElevel[UE]]++;
              drop_initial[initial_CElevel[UE]]++;
              flag[UE] = 2;
            }
          }
        }
      }

      int count[3] = {0};
      for(int j=0;j<N;j++){
        if(UE_CElevel[j] == 0 && flag[j] == 0) count[0]++;
        else if(UE_CElevel[j] == 1 && flag[j] == 0) count[1]++;
        else if(UE_CElevel[j] == 2 && flag[j] == 0) count[2]++;
      }

      for(int j=0;j<3;j++){
        if(count[j] == 0) slots_CElevel[j] = slot/T_b[j];
      }
    //  myfile << ack[0]+ack[1]+ack[2]+drop[0]+drop[1]+drop[2] << "\n";
      slot += T_b[0];
      }
      /*cout << N << ": ";
      for(int j=0;j<3;j++){
        cout << slots_CElevel[j] << " ";
      }
      cout << "\n";*/
      success_overall += (double)(ack[0]+ack[1]+ack[2]);
      delay_overall += (double)(meandelay[0]+meandelay[1]+meandelay[2])/((double)(ack[0]+ack[1]+ack[2]));
      success[0] += (double)(ack_initial[0]);
      success[1] += (double)(ack_initial[1]);
      success[2] += (double)(ack_initial[2]);
      delay[0] = (double)(meandelay[0])/((double)(ack_initial[0]));
      delay[1] = (double)(meandelay[1])/((double)(ack_initial[1]));
      delay[2] = (double)(meandelay[2])/((double)(ack_initial[2]));
      for(int j=0;j<3;j++){
        thr[j] += (double)(ack[j])/(double)slots_CElevel[j];
      }
    }
    myfile << arr[i] << "\n";
    myfile <<"success prob: " << success_overall/(arr[i]*100)  << "\n";
    myfile <<"success prob: " << success[0]/(arr[i]/3*100) << " " << success[1]/(arr[i]/3*100) << " " << success[2]/(arr[i]/3*100) << "\n";
    myfile << "meandelay_overall: " << delay_overall/100  << " " << "\n";
    myfile << "meandelay: " << delay[0]/100 << " " << delay[1]/100  << " "  << delay[2]/100<< "\n";
    myfile << "throughput: " << thr[0]/100 << " " << thr[1]/100 << " " << thr[2]/100 << "\n";
    
  }
  myfile <<  endl;

}
    myfile.close();
  return 0;
}