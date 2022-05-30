#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#define ATTACK_SUCCESS 0
#define ATTACK_FAIL 1

int get_pq(mpz_t phi, mpz_t n){
    mpz_t b, par, t;
    mpz_t p, q;
    mpz_inits(b, par, t, NULL);
    mpz_inits(p, q, NULL);

    // b = n - phi + 1
    mpz_sub(b, n, phi);
    mpz_add_ui(b, b, 1);

    // par = b * b - 4 * n
    mpz_mul(par, b, b);
    mpz_mul_ui(t, n, 4);
    mpz_sub(par, par, t);

    if(mpz_cmp_ui(par, 0) >= 0){
        mpz_sqrt(par, par);
        // p = (-b + par) / 2
        mpz_sub(t, par, b);
        mpz_fdiv_q_ui(p, t, 2);
        // q = (-b - par) / 2
        mpz_add(t, par, b);
        mpz_fdiv_q_ui(q, t, 2);
        mpz_mul_si(q, q, -1);

        mpz_abs(p, p);
        mpz_abs(q, q);

        mpz_mul(t, p, q);
        if(mpz_cmp(t, n) == 0) {
            gmp_printf("p = %Zd\n", p);
            gmp_printf("q = %Zd\n", q);
            return ATTACK_SUCCESS;
        }
    }
    mpz_clears(b, par, t, NULL);
    mpz_clears(p, q, NULL);
    return ATTACK_FAIL;
}

int qin_fun(mpz_t a, mpz_t m){
    mpz_t x11, x12, x21, x22;
    mpz_t x13, x23;

    mpz_inits(x11, x12, x21, x22, x13, x23, NULL);

    mpz_set_str(x11, "1", 10);
    mpz_set(x12, a);
    mpz_set_str(x21, "0", 10);
    mpz_set(x22, m);

    mpz_set_str(x13, "1", 10);
    mpz_fdiv_q(x23, m, a);

    mpz_t t, q, r, k, phi;
    mpz_inits(t, q, r, k, phi, NULL);

    while(mpz_cmp_ui(x12, 1)) {
        if (mpz_cmp(x22, x12)) {
            // q = (x22 - 1) // x12
            // r = x22 - q * x12
            mpz_fdiv_qr(q, r, x22, x12);
            // x21 = q * x11 + x21
            mpz_mul(t, q, x11);
            mpz_add(x21, t, x21);
            // c13 = q * x23 + x13
            mpz_mul(t, q, x23);
            mpz_add(x13, t, x13);
            // x22 = r
            mpz_set(x22, r);
        }

        if (mpz_cmp(x12, x22)) {
            mpz_fdiv_qr(q, r, x12, x22);
            // x21 = q * x21 + x11
            mpz_mul(t, q, x21);
            mpz_add(x11, t, x11);
            // x23 = q * x13 + x23
            mpz_mul(t, q, x13);
            mpz_add(x23, t, x23);
            // x12 = r
            mpz_set(x12, r);
        }

        mpz_mul(t, a, x21);
        mpz_sub_ui(t, t, 1);
        mpz_mod(k, x13, x21);

        if (mpz_cmp_ui(k, 0) == 0) {
            continue;
        }

        mpz_fdiv_qr(phi, t, t, k);
        if (mpz_cmp_ui(t, 0) == 0) {
            int ret = get_pq(phi, m);
            if (!ret) {
                gmp_printf("d = %Zd\n", x21);
                printf("attack success\n");
                return ATTACK_SUCCESS;
            }
        }
    }

    mpz_clears(x11, x12, x21, x22, x13, x23, NULL);
    mpz_clears(t, q, r, k, phi, NULL);
    return ATTACK_FAIL;
}

int main(int argc, char *argv[]) {
    mpz_t e, n;
    int ret = mpz_init_set_str(e, "15126654297964752013098236737142792343328885821043850717591212219416121876442886718732758175450185439250097909940465459448006358513001188315695951467846403260337198869714837909361928327989272855362432071137603123766827717346921751885958867720015317748270921597161083490383278302493913553369743780995203398626939715733755155009681289940104874444139325427474016608879888482717790115539038236875583889703891126293623009944822130924615253652912319543400303803395910987309654804989665931463997217772013338972458030372517101804468582533624114654185261016834363449414265885477703830170220100277420183737256953449921432442769", 10);
    if (ret != 0){
        perror("mpz for e error\n");
        exit(EXIT_FAILURE);
    }

    ret = mpz_init_set_str(n, "23873211071137189930614166310267339487454538068422443657969041262460444429964816431426710183695755476413937115540614428835263204196063562204136440332086975595534127489616794634958117262920797357760383121216527578368541040720097880511281265751148514970585852544357025892510419412343969413669659546355293839984987174937768419702376847760976489365521587044048554452410130309174187881781817343014915775915442567796307120118050011988970522886279315724310652960260354317732408237949885912477148109782713365688772833978483650246761301470938166706596058470226807335420535020271139433490249384246034110447894017222870344265949", 10);
    if (ret != 0){
        perror("mpz for n error\n");
        exit(EXIT_FAILURE);
    }

    ret = qin_fun(e, n);
    if (ret != 0){
        perror("attack fail\n");
        exit(EXIT_FAILURE);
    }

    mpz_clears(e, n, NULL);
    return EXIT_SUCCESS;
}
