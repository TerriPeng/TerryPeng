
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>

void set_random_seed();
int randn(int n);

struct mm_code_maker{

	void init(int i_length, int i_num){
    	length = i_length;
    	num = i_num;
	}

	void generate_sequence(){
    	for(int i = 0; i < length; i++){
        	sequence.push_back(randn(num));
    	}
	}

 	void give_feedback(const std::vector<int>& attempt, int& black_hits, int& white_hits){

    	black_hits=0;
    	white_hits=0;









for(int i=0; i<attempt.size(); i++){
        	if(attempt[i]==sequence[i]){
        	black_hits++;
        	}
    	}
    	int total_hits=0;
    	for(int j=0; j<num; j++){
        	int seq=0;
        	int attemp=0;
        	for(int i=0; i<sequence.size(); i++){
            	if(sequence[i]==j){
                	seq++;
            	}
            	if(attempt[i]==j){
                	attemp++;
            	}
        	}
        	if(seq<=attemp){
           	total_hits=total_hits+seq;
        	}
        	else{
           	total_hits=total_hits+attemp;
        	}
    	}
    	white_hits=total_hits-black_hits;
	}



	std::vector<int> sequence;

	int length;
	int num;
};

struct mm_solver{

	void init(int i_length, int i_num){
    	length = i_length;
    	num = i_num;
	}

	void all_pos(int length, int num){


    	for(int i=0; i<length; i++){
        	possibilities.push_back(0);
    	}
    	int situation;
    	situation=pow(num, length);
    	for( int i=1; i<=situation; i++){
        	for( int j=0; j<length; j++){
            	if(j==(length-1)){
                	possibilities[j]=(i-1)%num ;
            	}
            	else{
            	int note;
            	note=pow(num,(length-1-j));
            	possibilities[j]=(((i-1)/note))%num;
            	}
        	}
        	total_pos.push_back(possibilities);
    	}
	}

	void create_attempt(std::vector<int>& attempt){
    	int pos_size;
    	pos_size=pow(num, length);
    	if(total_pos.size()!=pos_size){
        	attempt=total_pos[randn(total_pos.size())];
    	}
    	else{
        	for(int i=0;i<(length/2);i++){
            	attempt.push_back(0);
        	}
        	for(int i=attempt.size();i<length;i++){
            	attempt.push_back(1);
        	}
    	}
	}


	void learn(std::vector<int>& attempt, int black_hits, int white_hits){

    	std::vector<std::vector<int> > remain_pos;
    	for(int i=0; i<total_pos.size(); i++){
        	int blackhits=0;
        	int whitehits=0;
        	give_feedback_2(total_pos[i] ,attempt, blackhits, whitehits);
        	if(blackhits==black_hits && whitehits==white_hits && total_pos[i]!=attempt){
            	remain_pos.push_back(total_pos[i]);
        	}
    	}
    	total_pos=remain_pos;
	}

	void give_feedback_2(const std::vector<int>& pos, std::vector<int> attempt, int& black_hits, int& white_hits){

    	for(int i=0; i<attempt.size(); i++){
        	if(attempt[i]==pos[i]){
        	black_hits++;
        	}
    	}
    	int total_hits=0;
    	for(int j=0; j<num; j++){
        	int seq=0;
        	int attemp=0;
        	for(int i=0; i<attempt.size(); i++){
            	if(attempt[i]==j){
                	seq++;
            	}
            	if(pos[i]==j){
                	attemp++;
            	}
        	}
        	if(seq<=attemp){
           	total_hits=total_hits+seq;
        	}
        	else{
           	total_hits=total_hits+attemp;
        	}
    	}
    	white_hits=total_hits-black_hits;
	}



	std::vector<int> possibilities;
	std::vector<std::vector<int> > total_pos;



	int length;
	int num;

};


/// the main is the same as in the previous example

int main(){
	/// write the code for the main here in order to test your functions
	/// our program uses random features so we need to call the function setting a random seed
	set_random_seed();

	int length, num;
	std::cout << "enter length of sequence and number of possible values:" << std::endl;
	std::cin >> length >> num;
	double count_all=0;
	std::cout << "你要皮几次？" << std::endl;
	std::cout << "How many times？" << std::endl;
	int turns,max=0;
	std::cin >> turns;
	if (pow(num, length)>20000000){
    	int Yes=99;
    	std::cout << "吃屎吧 算不过来,输入0继续" << std::endl;
    	std::cout << "Eat shit,enter 0 to continue" << std::endl;
    	std::cin >> Yes ;
    	if(Yes!=0){
        	exit(EXIT_FAILURE);
    	}
	}
	if (turns>10000){
    	int Yes=99;
    	std::cout << "皮一下可以，皮几万不行,输入0继续" << std::endl;
    	std::cout << "Pi yi xia ok, PGONE not ok,enter 0 to continue" << std::endl;
    	std::cin >> Yes ;
    	if(Yes!=0){
        	exit(EXIT_FAILURE);
    	}
	}
	clock_t start_time=time(NULL);
	for(int n=0;n<turns;n++){
    	mm_solver solver;
    	/// we declare an object of type mm_solver
    	solver.init(length, num);
    	/// we initialise the values for length and num

    	mm_code_maker maker;
    	/// we declare an object of type mm_code_maker
    	maker.init(length, num);
    	/// we initialise the values for length and num

    	maker.generate_sequence();
    	/// we generate a random sequence
    	solver.all_pos(length, num);
    	int black_hits=0, white_hits=0;
    	/// just some number to limit the number of attempts
    	int attempts_limit = 5000;
    	int attempts = 0;
    	while((black_hits < length) && (attempts < attempts_limit)){
        	std::vector<int> attempt;

        	solver.create_attempt(attempt);
        	/// the solver creates an attempt
        	maker.give_feedback(attempt, black_hits, white_hits);
        	/// we ask for feedback for the attempt

        	/// we print the attempt
        	std::cout << "attempt: " << std::endl;
        	for(int i = 0; i < attempt.size(); i++){
            	std::cout << attempt[i] << " ";
        	}
        	std::cout << std::endl;
        	/// we print the feedback
        	std::cout << "black pegs: " << black_hits << " " << " white pegs: " << white_hits << std::endl;
        	/// we give the feedback to the solver so that it can learn
        	solver.learn(attempt, black_hits, white_hits);
        	attempts++;
    	}

    	if(black_hits == length){
        	std::cout << "the solver has found the sequence in " << attempts << " attempts" << std::endl;
    	}
    	else{
        	std::cout << "after " << attempts << " attempts still no solution" << std::endl;
    	}
    	std::cout << "the sequence generated by the code maker was:" << std::endl;
    	for(int i = 0; i < maker.sequence.size(); i++){
        	std::cout << maker.sequence[i] << " ";
    	}
    	std::cout << std::endl;
    	count_all=count_all+attempts;
    	if (attempts>max) {
        	max=attempts;
    	}
	}
	clock_t end_time=time(NULL);
	double time=(double)(end_time-start_time);
	std::cout << "皮了 "<<turns <<" 次之后，发现" << std::endl;
	std::cout << "total attempts: " << count_all<< std::endl;
	double average=count_all;
	average=count_all/turns;
	std::cout << "average attempts: " << average<< std::endl;
	std::cout << "max attempt: " << max<< std::endl;
	std::cout << "总共皮了 " << time<< " 秒"<< std::endl;
	return 0;
}

void set_random_seed(){
	std::srand(std::time(0));
}

int randn(int n){
	return std::rand() % n;
}
