#include <bits/stdc++.h>
#include <iostream>
#include <random>
#include <vector>
#include <fstream>

using namespace std;

int main(){
	int arr[] = {900,3000,6000,9000,12000,15000,18000,21000,24000,27000,30000,33000,36000,39000,42000,45000,48000};
	/*vector<int> arr;
	int l = 24000;
	while(l<27000){
		arr.push_back(l);
		l += 30;
	}*/
//	int arr[] = {24300,24330,24360,24390,24420,24450,24480,24510,24540,24570,24600};
	int size = sizeof(arr)/sizeof(arr[0]);
	//int size = arr.size();
	int maxattempts[3] = {10,6,10};
	int globalAttempts = 10;
	int W[3] = {7,7,7}; 
	int T_b[3] = {80,160,320}; // in ms
	//int T_ok[3] = {68,152,476}; //in ms
	//int T_col[3] = {28,100,376}; // in ms
	int P[4] = {11,23,35,47};
	//double lam[] = {0.0000001389,0.000000278,0.000000555,0.00000138,0.0000033};
	double lam[] = {0.00000138};
	int iterations = 1;
	int size1 = sizeof(lam)/sizeof(lam[0]);
	ofstream myfile;
	myfile.open ("10610__352_121224_12min.txt");
	std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
	std::uniform_int_distribution<int>  distr(0,P[0]);
    std::random_device                  rand_dev1;
    std::mt19937                        generator1(rand_dev1());
    std::uniform_int_distribution<int>  distr1(P[0]+1,P[1]);
    std::random_device                  rand_dev2;
    std::mt19937                        generator2(rand_dev2());
    std::uniform_int_distribution<int>  distr2(P[1]+1,P[3]);
    std::random_device                  rand_dev3;
    std::mt19937                        generator3(rand_dev3());
    std::uniform_int_distribution<int>  distr3(0,W[0]);
    std::random_device                  rand_dev4;
    std::mt19937                        generator4(rand_dev4());
    std::uniform_int_distribution<int>  distr4(0,W[1]);
    std::random_device                  rand_dev5;
    std::mt19937                        generator5(rand_dev5());
    std::uniform_int_distribution<int>  distr5(0,W[2]);
    for(int a=0;a<size1;a++){
   		double lambda = lam[a];
   		double value = 1/lam[a];
   		//cout << value<<endl;
    	myfile << lam[a] << "-------------\n";
    	std::random_device rd; 
  		std::exponential_distribution<double> rng (lambda);
  		std::mt19937 rnd_gen (rd ());
  		/*std::random_device                  rand_dev7;
    	std::mt19937                        generator7(rand_dev7());
    	std::uniform_int_distribution<long long>  distr7(0,value);*/
    	/*std::random_device                  rand_dev6;
    	std::mt19937                        generator6(rand_dev6());
    	std::geometric_distribution<long long> distribution(lambda*T_b[0]);
    	std::random_device                  rand_dev7;
    	std::mt19937                        generator7(rand_dev7());
    	std::geometric_distribution<long long> distribution1(lambda*T_b[1]);
    	std::random_device                  rand_dev8;
    	std::mt19937                        generator8(rand_dev8());
    	std::geometric_distribution<long long> distribution2(lambda*T_b[2]);*/
    	for(int i=0;i<size;i++){
    	double success = 0;
    	double success_initial[3] = {0};
    	double dropped = 0;
    	double dropped_initial[3] = {0};
    	double collision_packets[6] = {0};
    	double delay[10] = {0};
    	double thr[3] = {0};
    	double thr1[3] = {0};
    	double transmission_slots[6] = {0};
    	long long packet_count1[3] = {0};
		long long packet_count2[3] = {0};
		long long packet_count3[3] = {0};
		
		double avg_attempts_overall[6] = {0};
		double ack22 = 0;
    	int a1=1;
    	int slot = 8;
    	while(a1-- > 0){
    		int N = arr[i];
    		cout << N <<endl;
    		int UE_CElevel[N];
    		int initial_CElevel[N];
    		int backoff[N];
			int delayperUE[N];
			double meandelay[6] = {0};
			int attempts[N];
			long long ack[3] = {0};
			double avg_num_attempts[6] = {0};
			long long drop[3] = {0};
			long long ack_initial[3] = {0};
			long long drop_initial[3] = {0};
			long long ack_CElevel[6] = {0};
			slot = 8; //in ms
			int T_start = 8; //in ms
			long long packet_arrival[N] = {0};
			long long initial_arrival[N] = {0};
			long long slots_CElevel[3] = {0};
			long long slot_start = 0;
			int s;
			for(int i=0;i<N;i++){
				//packet_arrival[i] = distr7(generator7);
				
				
				if(i< 0.3*N){
					packet_arrival[i] = (long long)rng (rnd_gen);
					//if(i== 0) cout << packet_arrival[i] << endl;
					UE_CElevel[i] = 0;
					initial_CElevel[i] = 0;
					attempts[i] = maxattempts[0];
				}
				else if(i < 0.8*N){
					
					packet_arrival[i] = (long long)rng (rnd_gen);
					//if(i== N/3+1) cout << packet_arrival[i] << endl;
					UE_CElevel[i] = 1;
					initial_CElevel[i] = 1;
					attempts[i] = maxattempts[1];
				}
				else{
					
					packet_arrival[i] = (long long)rng (rnd_gen);
					//if(i== 2*N/3+1) cout << packet_arrival[i] << endl;
		 			UE_CElevel[i] = 2;
		 			initial_CElevel[i] = 2;
		 			attempts[i] = maxattempts[2];
				}
				initial_arrival[i] = packet_arrival[i];	
			} 
			int P_total = 48;
    		while(slot < 43200008){
    			int flagSlot[P_total] = {0};
				vector<int> slotUE[P_total];
				for(int j=0;j<N;j++){
					if(UE_CElevel[j] == 0 && (slot-T_start)%T_b[0] == 0 && packet_arrival[j] < slot){
						if(packet_arrival[j] == initial_arrival[j]) initial_arrival[j] = slot;
						s = distr(generator);
						flagSlot[s]++;
						slotUE[s].push_back(j);
						transmission_slots[0]++;
						if(initial_CElevel[i] == 0){
							packet_count1[0]++;
						}
						else if(initial_CElevel[i] == 1){
							packet_count2[0]++;
						}
						else packet_count3[0]++;
					}

					if(UE_CElevel[j] == 1 && (slot-T_start)%T_b[1]==0 && packet_arrival[j] < slot){
						if(packet_arrival[j] == initial_arrival[j]) initial_arrival[j] = slot;
						s = distr1(generator);
						flagSlot[s]++;
						slotUE[s].push_back(j);
						if(initial_CElevel[j] == 0) transmission_slots[1]++;
						else transmission_slots[3]++;
						if(initial_CElevel[i] == 0){
							packet_count1[1]++;
						}
						else if(initial_CElevel[i] == 1){
							packet_count2[1]++;
						}
						else packet_count3[1]++;
					}

					if(UE_CElevel[j] == 2 && (slot-T_start)%T_b[2] == 0 && packet_arrival[j] < slot){
						if(packet_arrival[j] == initial_arrival[j]) initial_arrival[j] = slot;
						s = distr2(generator);
						flagSlot[s]++;
						slotUE[s].push_back(j);
						if(initial_CElevel[j] == 0) transmission_slots[2]++;
						else if(initial_CElevel[j] == 1) transmission_slots[4]++;
						else transmission_slots[5]++;
						if(initial_CElevel[i] == 0){
							packet_count1[2]++;
						}
						else if(initial_CElevel[i] == 1){
							packet_count2[2]++;
						}
						else packet_count3[2]++;
					}
				}

				for(int j=0;j<P_total;j++){
					if(flagSlot[j] == 1){
						int UE = slotUE[j][0];
			
							ack[UE_CElevel[UE]]++;
							ack_initial[initial_CElevel[UE]]++;
					
						if(UE_CElevel[UE] == 0){
							 ack_CElevel[0]++;
							 avg_num_attempts[0] += maxattempts[0]-attempts[UE]+1;
						}
						if(UE_CElevel[UE] == 1 && initial_CElevel[UE] == 0){
							avg_num_attempts[1] += maxattempts[1]-attempts[UE]+1;	
							ack_CElevel[1]++;
						} 
						else if(UE_CElevel[UE] == 1 && initial_CElevel[UE] == 1){
							ack_CElevel[3]++;
							avg_num_attempts[3] += maxattempts[1]-attempts[UE]+1;		
						} 
						if(UE_CElevel[UE] == 2 && initial_CElevel[UE] == 0){
							ack_CElevel[2]++;
							avg_num_attempts[2] += maxattempts[2]-maxattempts[1]-maxattempts[0]-attempts[UE]+1;	
						}
						else if(UE_CElevel[UE] == 2 && initial_CElevel[UE] == 1){
							ack_CElevel[4]++;
							avg_num_attempts[4] += maxattempts[2]-maxattempts[1]-attempts[UE]+1;	
						}
						else if(UE_CElevel[UE] == 2 && initial_CElevel[UE] == 2){
							ack_CElevel[5]++;
							avg_num_attempts[5] += maxattempts[2]-attempts[UE]+1;	
						}
						packet_arrival[UE] = slot+T_b[UE_CElevel[UE]];
						/*if(initial_arrival[UE] <= 8) initial_arrival[UE] = T_start;
						else if(initial_arrival[UE] > (ceil((double)initial_arrival[UE]/(double)T_b[initial_CElevel[UE]])-1)*T_b[initial_CElevel[UE]]+T_start) initial_arrival[UE] = ceil((double)initial_arrival[UE]/(double)T_b[initial_CElevel[UE]])*T_b[initial_CElevel[UE]]+T_start;
						else	initial_arrival[UE] = (initial_arrival[UE]/T_b[initial_CElevel[UE]])*T_b[initial_CElevel[UE]]+T_start; */
						meandelay[initial_CElevel[UE]] += (double)(packet_arrival[UE]-initial_arrival[UE])/1000;
						if(initial_CElevel[UE] == 0) packet_arrival[UE] = packet_arrival[UE] + (long long)rng (rnd_gen);
						else if(initial_CElevel[UE] == 1) packet_arrival[UE] = packet_arrival[UE] + (long long)rng (rnd_gen);
						else if(initial_CElevel[UE] == 2) packet_arrival[UE] = packet_arrival[UE] + (long long)rng (rnd_gen);
						initial_arrival[UE] = packet_arrival[UE];
						UE_CElevel[UE] = initial_CElevel[UE];
						attempts[UE] = maxattempts[initial_CElevel[UE]];
					}
					else if(flagSlot[j] > 1){
						for(int k=0;k<slotUE[j].size();k++){
							int UE = slotUE[j][k];
							attempts[UE]--;
							int CElevel = UE_CElevel[UE];
							if(initial_CElevel[UE] == 0 && j < 12){
								collision_packets[0]++;
							}
							else if(initial_CElevel[UE] == 0 && j < 24 && j>11){
								collision_packets[1]++;
							}
							else if(initial_CElevel[UE] == 0 && j < 48 && j>23) collision_packets[2]++;
							else if(initial_CElevel[UE] == 1 && j < 24 && j>11) collision_packets[3]++;
							else if(initial_CElevel[UE] == 1 && j < 48 && j>23) collision_packets[4]++;
							else if(initial_CElevel[UE] == 2 && j < 48 && j>23) collision_packets[5]++;
							packet_arrival[UE] = slot+T_b[UE_CElevel[UE]];
							if(attempts[UE] == 0 && CElevel < 2){
								if((CElevel == 1 && initial_CElevel[UE]==1) || (CElevel == 0 && initial_CElevel[UE]== 0)){
                					attempts[UE] = max(0,min(maxattempts[CElevel+1],globalAttempts- maxattempts[CElevel]));
              					}
              					else if(CElevel == 1 && initial_CElevel[UE] == 0){
                					attempts[UE] = max(0,min(maxattempts[CElevel+1],globalAttempts- maxattempts[CElevel]-maxattempts[CElevel-1]));
              					}
								if(attempts[UE] == 0){
									//cout << "a" << endl;
                					drop[UE_CElevel[UE]]++;
                					drop_initial[initial_CElevel[UE]]++;
                					avg_num_attempts[initial_CElevel[UE]] += 10 ;	
									/*if(initial_arrival[UE] <= 8) initial_arrival[UE] = T_start;
									else if(initial_arrival[UE] > (ceil((double)initial_arrival[UE]/(double)T_b[initial_CElevel[UE]])-1)*T_b[initial_CElevel[UE]]+T_start) initial_arrival[UE] = ceil((double)initial_arrival[UE]/(double)T_b[initial_CElevel[UE]])*T_b[initial_CElevel[UE]]+T_start;
									else	initial_arrival[UE] = (initial_arrival[UE]/T_b[initial_CElevel[UE]])*T_b[initial_CElevel[UE]]+T_start; */
									meandelay[initial_CElevel[UE]+3] += (double)(packet_arrival[UE]-initial_arrival[UE])/1000;
									if(initial_CElevel[UE] == 0) packet_arrival[UE] = packet_arrival[UE] + (long long)rng (rnd_gen);
									else if(initial_CElevel[UE] == 1) packet_arrival[UE] = packet_arrival[UE] + (long long)rng (rnd_gen);
									else if(initial_CElevel[UE] == 2) packet_arrival[UE] = packet_arrival[UE] + (long long)rng (rnd_gen);
									initial_arrival[UE] = packet_arrival[UE];
									//if(initial_CElevel[UE] == 2) attempts[UE] = globalAttempts;
									attempts[UE] = maxattempts[initial_CElevel[UE]];
									UE_CElevel[UE] = initial_CElevel[UE];
              					}
              					else{
                					UE_CElevel[UE] = CElevel+1;
                					CElevel = CElevel+1;
              					}
							}
							else if(attempts[UE] != 0){
								if(CElevel == 0){
									packet_arrival[UE] += distr3(generator3)*T_b[0]; 
								}
								else if(CElevel == 1){
									packet_arrival[UE] += distr4(generator4)*T_b[1]; 
								}
								else if(CElevel == 2){
									packet_arrival[UE] += distr5(generator5)*T_b[2]; 
								}
							}

							if(attempts[UE] == 0 && CElevel == 2){
								drop[UE_CElevel[UE]]++;
								drop_initial[initial_CElevel[UE]]++;
								if(initial_CElevel[UE] == 0){
									avg_num_attempts[0] += maxattempts[0];
									avg_num_attempts[1] += maxattempts[1];
									avg_num_attempts[2] += maxattempts[2]-maxattempts[1]-maxattempts[0];
								}
								else if(initial_CElevel[UE] == 1){
									avg_num_attempts[3] += maxattempts[1];
									avg_num_attempts[4] += maxattempts[2]-maxattempts[1];
								}
								else{
									avg_num_attempts[5] += 10;
								}	
								/*if(initial_arrival[UE] <= 8) initial_arrival[UE] = T_start;
								else if(initial_arrival[UE] > (ceil((double)initial_arrival[UE]/(double)T_b[initial_CElevel[UE]])-1)*T_b[initial_CElevel[UE]]+T_start) initial_arrival[UE] = ceil((double)initial_arrival[UE]/(double)T_b[initial_CElevel[UE]])*T_b[initial_CElevel[UE]]+T_start;
								else	initial_arrival[UE] = (initial_arrival[UE]/T_b[initial_CElevel[UE]])*T_b[initial_CElevel[UE]]+T_start; */
								meandelay[initial_CElevel[UE]+3] += (double)(packet_arrival[UE]-initial_arrival[UE])/1000;
								if(initial_CElevel[UE] == 0) packet_arrival[UE] = packet_arrival[UE] + (long long)rng (rnd_gen);
								else if(initial_CElevel[UE] == 1) packet_arrival[UE] = packet_arrival[UE] + (long long)rng (rnd_gen);
								else if(initial_CElevel[UE] == 2) packet_arrival[UE] = packet_arrival[UE] + (long long)rng (rnd_gen);
								initial_arrival[UE] = packet_arrival[UE];
								UE_CElevel[UE] = initial_CElevel[UE];
								//if(initial_CElevel[UE] == 2) attempts[UE] = globalAttempts;
								attempts[UE] = maxattempts[initial_CElevel[UE]];
							}
						}
					}
				}
				slot += T_b[0];
    	}
    	
    	success += (double)(ack[0]+ack[1]+ack[2]);
    	dropped += (double)(drop[0]+drop[1]+drop[2]);
    	//cout << ack[0] << " " << ack[1] << " " << ack[2] << endl;
    	for(int j=0;j<3;j++){
    		delay[j] += meandelay[j]/(ack_initial[j]);
    		delay[j+3] += meandelay[j+3]/(drop_initial[j]);
    		delay[j+6] += ((meandelay[j]+meandelay[j+3])/(ack_initial[j]+drop_initial[j]));
    	}
    	delay[9] += ((meandelay[0]+meandelay[1]+meandelay[2]+meandelay[3]+meandelay[4]+meandelay[5])/(ack_initial[0]+ack_initial[1]+ack_initial[2]+drop_initial[0]+drop_initial[1]+drop_initial[2])); 
    	//if(ack_initial[0]+ack_initial[1]+ack_initial[2]+drop_initial[0]+drop_initial[1]+drop_initial[2] == ack[0]+ack[1]+ack[2]+drop[0]+drop[1]+drop[2]) cout << 1 << endl;
    	int m = 0;
    	for(int j=0;j<3;j++){
    		success_initial[j] += (double)ack_initial[j];
    		dropped_initial[j] += (double)drop_initial[j];
    		thr[j] += (double)(ack[j])/(double)(slot/T_b[j]);
    	}
    	for(int j=0;j<6;j++){
       		if(j == 2 || j==5 || j==6) avg_num_attempts[j] = avg_num_attempts[j]/(ack_CElevel[j]+drop_initial[j]);
       		else{
       			avg_num_attempts[j] = avg_num_attempts[j]/(ack_CElevel[j]);
       		}
    		avg_attempts_overall[j] += avg_num_attempts[j];
    	}
    	
    	thr1[0] = thr1[0]+(double)(ack_CElevel[0])/(double)((slot)/T_b[0])+(double)(ack_CElevel[1])/(double)((slot)/T_b[1])+(double)(ack_CElevel[2])/(double)((slot)/T_b[2]);
    	thr1[1] = thr1[1]+(double)(ack_CElevel[3])/(double)((slot)/T_b[1])+(double)(ack_CElevel[4])/(double)((slot)/T_b[2]);
    	thr1[2] = thr1[2]+(double)(ack_CElevel[5])/(double)((slot)/T_b[2]);

    }
    
    myfile << arr[i] << "\n";
  //  myfile << "success prob: " << success/(success+dropped) << "\n";
    //myfile << "success prob in initial_CElevel: " << success_initial[0]/(success_initial[0]+dropped_initial[0]) << " " << success_initial[1]/(success_initial[1]+dropped_initial[1]) << " " << success_initial[2]/(success_initial[2]+dropped_initial[2]) << "\n";
    myfile << "meandelay: " << delay[0]/iterations << " " << delay[1]/iterations << " " << delay[2]/iterations << " " << delay[3]/iterations << " " << delay[4]/iterations << " " << delay[5]/iterations << " " << delay[6]/iterations << " " << delay[7]/iterations <<" " << delay[8]/iterations << " " << delay[9]/iterations <<"\n";
     myfile << "coll prob: " << collision_packets[0]/(iterations*slot/T_b[0]) << " " << collision_packets[1]/(iterations*slot/T_b[1]) << " " << collision_packets[2]/(iterations*slot/T_b[2]) << " " << collision_packets[3]/(iterations*slot/T_b[1]) << " " << collision_packets[4]/(iterations*slot/T_b[2]) << " " << collision_packets[5]/(iterations*slot/T_b[2]) <<"\n";
    myfile << "avg attempts: " << avg_attempts_overall[0]/iterations << " " << avg_attempts_overall[1]/iterations << " " << avg_attempts_overall[2]/iterations  << " " << avg_attempts_overall[3]/iterations << " " << avg_attempts_overall[4]/iterations << " " << avg_attempts_overall[5]/iterations << endl;
    myfile << "avg load: " << transmission_slots[0]/(iterations*slot/T_b[0]) << " " << (transmission_slots[1])/(iterations*slot/T_b[1])  << " " << (transmission_slots[2])/(iterations*slot/T_b[2]) << " " << transmission_slots[3]/(iterations*slot/T_b[1]) << " " << (transmission_slots[4])/(iterations*slot/T_b[2])  << " " << (transmission_slots[5])/(iterations*slot/T_b[2]) << endl;
    myfile << "throughput: " << thr[0]/iterations << " " << thr[1]/iterations<< " " << thr[2]/iterations << "\n";
    myfile << "throughput of packet: " << thr1[0]/iterations << " " << thr1[1]/iterations << " " << thr1[2]/iterations << "\n";
    //myfile << "meandelay: " << delay[6] << " " << delay[7] <<" " << delay[8] << " " << delay[9]<<"\n";
   // myfile << "thr: " << (double)ack_CElevel[0]/(5400000) << " " << (double)ack_CElevel[1]/(2700000) << " " << (double)ack_CElevel[2]/(675000) << " " << (double)ack_CElevel[3]/(2700000) << " " << (double)ack_CElevel[4]/(675000) << " " << (double)ack_CElevel[5]/(675000) << "\n";
    /*for(int j=0;j<6;j++){
    	if(j==0) transmission_slots[j] = (double)transmission_slots[j]/(43200000/T_b[j]);
    	else if(j==1 || j==3) transmission_slots[j] = (double)transmission_slots[j]/(43200000/T_b[1]);
    	else if(j==2 || j==4 || j==5) transmission_slots[j] = (double)transmission_slots[j]/(43200000/T_b[2]);
    	transmission_slots[j] = (double)transmission_slots[j]/180000;
    }
    myfile << "transmission prob: ";
    for(int j=0;j<6;j++){
    	myfile << transmission_slots[j] << " ";
    }*/
    myfile << endl;
	}
	}
    myfile.close();
	return 0;
}