#pragma warning(disable:4996)
#include <stdio.h>
#define 기본시급 12000
#define 추가분급 100
#define 부양가족환급 2000


int main()
{ 
    int age, family, second, checkcard, creditcard, num = 0; //사원번호,나이,일한시간,카드사용액
    char departcode; //부서코드
    int wkhour, wkmin; //시간을 시, 분으로 나눈것
    int tsec; //시간,분 계산에서의 중간변수
    int maxwkhours; //최대근로가능시간
    int ovwkhour, ovwkmin; //초과 근로 시간을 시,분으로
    double salary; //세전 소득액
    int resalary; //세전 소득액 소수점 첫째자리
    double taxsalary; //세후 소득액
    int retaxsalary; //세후 소득액 소수점 첫째자리
    double tax; //세금
    int retax; //세금의 소수점 첫째자리
    double reffamily, refcheck, refcredit; //부양가족인당 환급금, 체크/신용카드사용당 환금금
    double refsalary; //환금금 중간변수
    int rerefsalary; //환급금 소수점 첫째자리
    int error; //오류검출

    printf("사원번호를 입력해주세요:");
    scanf("%d",&num);
    printf("나이를 입력해주세요:");
    scanf("%d",&age);
    printf("(단 부서코드는 알파벳 대문자로 A~O 사이입니다.)\n");
    printf("부서코드를 입력해주세요:");
    scanf(" %c",&departcode);
    printf("(근무시간은 초로 입력해주세요.)\n");
    printf("근무시간을 입력해주세요:");
    scanf("%d",&second);
    printf("부양 가족수를 입력해주세요:");
    scanf("%d",&family);
    printf("신용카드사용액을 입력해주세요:");
    scanf("%d",&creditcard);
    printf("체크카드사용액을 입력해주세요:");
    scanf("%d",&checkcard);
    printf("\n\n\n\n");
    
    /* 오류 검출 */

    if ( age <=0 ){ //나이 범위 검사
        error = 1;
    }
    else if ( 'A' > departcode || departcode > 'O'){ //부서코드 범위 검사
        error = 1;
    }
    else if ( num <= 0 ){ //사원번호 음수,0 검사
        error = 1;
    }
    else if ( second < 0 ){ //시간초 음수 검사
        error = 1;
    }
    else if ( family < 0 ){ //부양가족수 음수 검사
        error = 1;
    }
    else if ( creditcard < 0 ){ //신용카드사용액 음수검사
        error = 1;
    }
    else if ( checkcard < 0 ){ //체크카드 사용액 음수검사
        error = 1;
    }

    if ( error == 1 ){
        printf("자료가 잘못 입력되었습니다.\n프로그램을 종료합니다.");
    }
    else{

        /* 일한 시간, 분 계산 */

        tsec = second % 3600;
        wkhour = second / 3600; // 시 구하기
        wkmin = tsec / 60; // 분 구하기

        if ( tsec % 60 != 0 ){ //초부분을 올림처리
        wkmin++;
        }

        /* 나이별 최대인정근로가능시간 */

        if ( age <= 0 ){
    
        }
        else if ( age < 18 ){
            maxwkhours = 0;
        }
        else if ( age < 25 ){
            maxwkhours = 7;
        }
        else if ( age < 55 ){
            maxwkhours = 9;
        }
        else if ( age < 65 ){
            maxwkhours = 5;
        }
        else{
            maxwkhours = 3;
        }
    
        /* 나이별 최대 근로가능시간에 따른 소득액 계산 */

        if ( wkhour > maxwkhours ){
            ovwkhour = wkhour - maxwkhours;
            ovwkmin = wkmin;
            wkmin = 0;
            salary = (( (double)maxwkhours * (double)기본시급 ) + (( (double)ovwkhour * 60.0 ) + (double)ovwkmin ) * (double)추가분급 );
        }
        else{
            ovwkhour = 0;
            ovwkmin = 0;
            salary = ( (double)기본시급 / 60.0 ) * (( (double)wkhour * 60.0 ) + (double)wkmin );
        }

        resalary = (int)( salary * 10.0 ) % 10; //세전급여액의 소수점 1의 자리수 추출
        if ( resalary > 5 ){ //세전급여액 반올림
            salary += 1.0;
        }
    
        /* 소득액에 따른 세금의 계산 및 저장 */

        if ( salary < 30000 ){
            taxsalary = (double)salary * 9.5;
            tax = (double)salary * 0.5;
        }
        else{
            taxsalary = (double)salary * 8.5;
            tax = (double)salary * 1.5;
        }

        retax = (int)( tax * 10.0 ) % 10;
        if( retax > 5 ){
            tax += 1.0;
        }

        resalary = (int)( taxsalary * 10.0 ) % 10; //세후급여액의 소수점 1의 자리수 추출
        if ( resalary > 5 ){ // 세후급여액 반올림
            taxsalary += 1.0;
        }

        /* 환급금 계산 */

        reffamily = family * 부양가족환급; //부양가족인당 환급금 계산
    
        if ( (double)creditcard > ( salary * 0.3 ) ){ //신용카드 사용에 따른 환급금 계산
            refcredit = ( (double)creditcard - ( salary * 0.3 ) ) * 0.1;
        }
        else{
        refcredit = 0.0;
        }

        if ( (double)checkcard > ( salary * 0.3 ) ){ //체크카드 사용에 따른 환급금 계산
            refcheck = ( (double)checkcard - ( salary * 0.3 ) ) * 0.3;
        }
        else{
            refcheck = 0.0;
        }
    
        refsalary = (double)reffamily + refcredit + refcheck; //환급금의 총합
        rerefsalary = (int)( refsalary * 10.0 ) % 10; //홥금금의 소수점 첫째자리 추출
        if ( rerefsalary > 5 ){ //환급금 반올림
            refsalary += 1;
        }

        //출력

        printf("사원번호: %d\n",num); //사원번호 출력
        if ( departcode == 'A' ){ //부서 출력
            printf("부서: 경영지원팀");
        }
        else if ( departcode == 'B' ){
            printf("부서: 총무팀");
        }
        else if ( departcode == 'C' ){
            printf("부서: 영업팀");
        }
        else if ( departcode == 'D' ){
            printf("부서: 구매팀");
        }
        else if ( departcode == 'E' ){
            printf("부서: 전산팀");
        }
        else if ( departcode == 'F' ){
            printf("부서: 마케팅팀");
        }
        else if ( departcode == 'G' ){
            printf("부서: 인사팀");
        }
        else if ( departcode == 'H' ){
            printf("부서:기획팀");
        }
        else if ( departcode == 'I' ){
            printf("부서: 연구개발팀");
        }
        else if ( departcode == 'J' ){
            printf("부서: 생산관리팀");
        }
        else if ( departcode == 'K' ){
            printf("부서: 생산연구팀");
        }
        else if ( departcode == 'L' ){
            printf("부서: 품질관리팀");
        }
        else if ( departcode == 'M' ){
            printf("부서: 해외영업팀");
        }
        else if ( departcode == 'N' ){
            printf("부서: SW개발팀");
        }
        else if ( departcode == 'O' ){
            printf("부서: 서버관리팀");
        }
        printf("\n");//줄바꿈
        printf("근무시간: %d시%d분\n",maxwkhours, wkmin); //근무시간 출력
        printf("초과근무시간: %d시%d분\n",ovwkhour,ovwkmin); //초과근무시간 출력
        printf("세전급여액: %d\n",(int)salary); //세전급여액 출력
        printf("세후급여액: %d\n",(int)taxsalary);//세후급여액 출력
        printf("세금: %d\n",(int)tax); //세금 출력
        printf("환급금: %d\n",(int)refsalary); //환급금 출력

        return 0;
    }
}
