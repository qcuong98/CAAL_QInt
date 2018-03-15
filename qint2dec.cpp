#include <stdlib.h>
#include <string.h>
#include "QInt.h"

#define MAX_LEN 40

const char *POWER_OF_TWO[128] = {
    "1000000000000000000000000000000000000000", "2000000000000000000000000000000000000000",
    "4000000000000000000000000000000000000000", "8000000000000000000000000000000000000000",
    "6100000000000000000000000000000000000000", "2300000000000000000000000000000000000000",
    "4600000000000000000000000000000000000000", "8210000000000000000000000000000000000000",
    "6520000000000000000000000000000000000000", "2150000000000000000000000000000000000000",
    "4201000000000000000000000000000000000000", "8402000000000000000000000000000000000000",
    "6904000000000000000000000000000000000000", "2918000000000000000000000000000000000000",
    "4836100000000000000000000000000000000000", "8672300000000000000000000000000000000000",
    "6355600000000000000000000000000000000000", "2701310000000000000000000000000000000000",
    "4412620000000000000000000000000000000000", "8824250000000000000000000000000000000000",
    "6758401000000000000000000000000000000000", "2517902000000000000000000000000000000000",
    "4034914000000000000000000000000000000000", "8068838000000000000000000000000000000000",
    "6127776100000000000000000000000000000000", "2344553300000000000000000000000000000000",
    "4688017600000000000000000000000000000000", "8277124310000000000000000000000000000000",
    "6545348620000000000000000000000000000000", "2190786350000000000000000000000000000000",
    "4281473701000000000000000000000000000000", "8463847412000000000000000000000000000000",
    "6927694924000000000000000000000000000000", "2954399858000000000000000000000000000000",
    "4819689717100000000000000000000000000000", "8638379534300000000000000000000000000000",
    "6376749178600000000000000000000000000000", "2743598347310000000000000000000000000000",
    "4496097784720000000000000000000000000000", "8883185579450000000000000000000000000000",
    "6777261159901000000000000000000000000000", "2555523209912000000000000000000000000000",
    "4011156408934000000000000000000000000000", "8022203906978000000000000000000000000000",
    "6144406812957100000000000000000000000000", "2388802734815300000000000000000000000000",
    "4667714478630700000000000000000000000000", "8235538847370410000000000000000000000000",
    "6560176794741820000000000000000000000000", "2131243599492650000000000000000000000000",
    "4262486099985211000000000000000000000000", "8425863189971522000000000000000000000000",
    "6940737269953054000000000000000000000000", "2990474529917009000000000000000000000000",
    "4891849058934108100000000000000000000000", "8693698107978206300000000000000000000000",
    "6397297304957502700000000000000000000000", "2785585708815114410000000000000000000000",
    "4471171516730328820000000000000000000000", "8843243032570646750000000000000000000000",
    "6796486064051292511000000000000000000000", "2593963129003485032000000000000000000000",
    "4097837248106861164000000000000000000000", "8085774586302733229000000000000000000000",
    "6161559073704476448100000000000000000000", "2323019147418843986300000000000000000000",
    "4646028384926796873700000000000000000000", "8292146769852593757410000000000000000000",
    "6585282539715097415920000000000000000000", "2171565078530185920950000000000000000000",
    "4243031147170261950811000000000000000000", "8486062284341423811632000000000000000000",
    "6963125469682846632274000000000000000000", "2937240929375692374449000000000000000000",
    "4874580858741395649888100000000000000000", "8659071617592681398777300000000000000000",
    "6319143234195273687555700000000000000000", "2728386468281547275111510000000000000000",
    "4456763927563094541322030000000000000000", "8803537854137089092644060000000000000000",
    "6716074719264169185298021000000000000000", "2532149438529229361587142000000000000000",
    "4074288966158548723075384000000000000000", "8049467933307196556041769000000000000000",
    "6188925976604383113182439100000000000000", "2367950953318667226265868300000000000000",
    "4625911817626335542521737700000000000000", "8250932634352760194052474510000000000000",
    "6501874278605431289005849030000000000000", "2112659447310962469100798160000000000000",
    "4224219984720835829300497321000000000000", "8448428979450670758700885742000000000000",
    "6986946959901251417510671594000000000000", "2973992919912403824130253099000000000000",
    "4857895838934806658260407089100000000000", "8615791776978612317521804169300000000000",
    "6330593453957334624152618229700000000000", "2760097807815768258205236548510000000000",
    "4431085714730537507500562196130000000000", "8862061538470074114110035283360000000000",
    "6735023076941049228220060567621000000000", "2570146043992088546540021035352000000000",
    "4051282186895067192190042060705000000000", "8003465263791125385281084021410100000000",
    "6106821527493240761563069042820200000000", "2302752054987480433037029184650400000000",
    "4604415009875961866064148369211800000000", "8218820108751933633129286729522610000000",
    "6526750206513876276248563558154230000000", "2152511402136653543586137017309460000000",
    "4205032804262317096073364124708921000000", "8400164618425624183147629248416952000000",
    "6900229236940358267284358586922915000000", "2910448562990607525569607173954830100000",
    "4830886135891214150139314347819670200000", "8670673360793428201268728684738351400000",
    "6351257621497846502427556379476703800000", "2703405352885792114844113749943516610000",
    "4416800705671595228698226498996032330000", "8822710410353091546397542987993164660000",
    "6754430820607083092785194875997229231000", "2519860650214167085471389651995548562000",
    "4038731211428225161943669313891196135000", "8066572422846540323896239726693283360100",
    "6123155844692190646693568552397467621200", "2346201798295281292397037115685925352400",
    "4682502497581563485685164320371950705800", "8275014885173037861371329640643811410710",
};

static void add(char *a, const char *b) {
    int rem = 0;
    for (int i = 0; i < MAX_LEN; i++) {
        rem = rem + a[i] + b[i] - '0' - '0';
        if (rem > 9) {
            a[i] = rem - 10 + '0';
            rem  = 1;
        } else {
            a[i] = rem + '0';
            rem  = 0;
        }
    }
}

static char *zero() {
    char *s = (char *)malloc(MAX_LEN + 1);
    memset(s, '0', MAX_LEN);
    s[MAX_LEN] = 0;
    return s;
}

static void reverse(char *s) {
    for (int i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        char tmp = s[i];
        s[i]     = s[j];
        s[j]     = tmp;
    }
}

char *QInt2Dec(const QInt &q) {
    char *res = zero();
    QInt x    = (q.data[N - 1] >> 31) ? -q : q;
    for (int i = 0, bit = 0; i < N; i++) {
        for (int j = 0; j < 32; j++, bit++) {
            if ((x.data[i] >> j) & 1)
                add(res, POWER_OF_TWO[bit]);
        }
    }
    for (int i = MAX_LEN - 1; i > 0 && res[i] == '0'; i--)
        res[i] = 0;
    if (q.data[N - 1] >> 31)
        res[strlen(res)] = '-';
    reverse(res);
    return res;
}