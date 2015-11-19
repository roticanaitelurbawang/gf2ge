//
//  main.c
//  roti GF2 GE solver
//
//  Created by Loh Hong Khai on 10/13/15.
//  Copyright (c) 2015 Loh Hong Khai. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NUM_BITS_IN_TYPE 64 // size of unsigned long. Change if necessary.

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))


int main(int argc, const char * argv[]) {
    
    FILE* fr;   // pointer to file for opening
    
    for (int iter = 1; iter < 100;) {
        int dimen = 512;    // bitlength/row number of the message matrix

        /* IMPORT DATA */
        char line[1024];    //1024bytes maximum per line imported from file
        char **inputdata;

        // assumes that the GF2 matrix is represented by hexa-decimal characters
        // allocate dimen+10 rows to import. 10 extra rows(symbols) needed for 99.99% PCD.
        // allocate bitlength*(2)/(4 bits per character)
        // --- *2 because random gen matrix concatenated with msg matrix
        inputdata = malloc((dimen+10) * sizeof(char*));
        for (int i = 0; i < (dimen+10); i++)
            inputdata[i] = malloc((dimen/2)+1 * sizeof(char));
        
        char* filename[10];     // memory alloc for import filename. 10 means the name can be at most 10 characters.
        sprintf(filename, "%d_%d.txt", dimen,iter);     // import file name format
        fr = fopen (filename, "rt");  /* open the file for reading */
        /* ***.txt is the name of the file */
        /* "rt" means open the file for reading text */
        
        int tempi = 0;
        while(fgets(line, 1024, fr) != NULL)    // 1024 characters to be read; tally with size of line
        {
            strncpy(inputdata[tempi], line, dimen/2);
            inputdata[tempi][dimen/2] = '\0';
            tempi++;
        }
        fclose(fr);  /* close the file prior to exiting the routine */
 
        // Example of data imported
//    char* inputdata[] = {"078f06d89fb8886185d051324b1f19464fd098f39a1c56ec82ff9bb6562d9bab", "6b692d592f85a320c0d589ca16ea90e9eaadf64b97638160b0371fe49216df45", "c9c3e210318d414190899246ea9c89bf69c9cba0a98f21bfe180eec6c62e4288", "fa9b4fb0503e021ad216457ea749515ea5f9b4bd1eef85cc4565b69c1089a7f4", "93dcea3288d2a28612a8c5d29f19b58dafb4181c4654427383426d2a7bdb0ed3", "8c9abfd31cd2c56e17b4936d9cc321cb36ff384be0c267f97a1fdc7a1a8e3a6d", "df908b8500a0c3864eae5320ac10c0da7c6aac36687264a8afb6f08cf3f76e39", "b02d792645d485f857ea811ee8c1a6b0390c97699725bfa0b548822ea93257a2", "71607c9d9e42639f5828d6f2178d105813da6aefa920d549df3daa6ecb183d98", "758c3477a02e92c67fc7c8a7ec55f6024bfa3ce5086d65f194defde97cfdd3c2", "6159d3e9b8321105fce1d78b597b67ef0e0b3ed3bea4d1ae208cc3b3ada60b53", "3fd74a6478a6e66fbd6ed6e71cc45f631c1e260b8091a99d10060a6bb338a250", "cf5f9f9226c95df3efce058006d922ee3dc5d4cf70984985cba7af35c91a7d06", "3deeadbd182b711a4bd1af1794e42e1377b69e40fcbea784884ca4041e044be6", "e3d72d16aadf2e62e55165cf88f8514385df3362d73b8eb91bd85e15c5fc707f", "287c41c71f9e9781bd6e581697f6d76f014c18940a36ab3a1861a632da20af52", "6fb70f9443a31de9d8929063e1b870517acaf6f066a86787c670b2fd844cc1f6", "19a5fe24f1d7e6de2a21ca12b9c126acf830ce39b61904f52a5da60d7dc0b437", "1f54296689ffd50892574a6c255618994a8544926af3b5f5596d3cb206194e08", "6c408d06b4ecd80ca97a6f53b7e328190633e22d0b6f71274b96fb919940b2eb", "b7e72354feabf16b3a008fd00ba805c9d9480a4ab4b37ee482dd3a40bd560b40", "314e1127d74bdb33c25b2319895213fda939a384801864b1cb06f9b05b2a6c11", "7bb1b6a77f54fbc867bac47e9f08ee7b5f9c1c5db3d26f6b2e31bbb7126d6bab", "f68855dda73c1acf8b18da051c8cbde012ab2b7eab7ea222de2a765d79e64d36", "b1620695e75bcd3a696c5aedd32d600980176ca792451818b683497b85b0b8d1", "0ca2336386209aba8cb3ffd20522c4b0b76f3db4d9ed3c01ea33ec99c6bd0ba0", "c6263cffaab7303c92ad3250eba90df93369c7278a4e44d3aaebcf23fdbb6b7e", "faa9ef016c52d04f45abc33a28426beafc2e1677998991f4cb4b113fbea775cd", "011b9bf8337ccddd5e109af00a8c89a23053883a8195bd3514d767a494eb86b1", "dd3400e200df78a6701206808764763ef28b98e4aaca1a8ac3afe4cc61e429eb", "0779284ce9d4ebef9ad284734d033ccd442219aa9b3e15744316c01f06aa33fa", "281446b91e2c130fa91aa8b0b8987157e44165005449ef6a7b57046dd1c7d9d0", "30ca8a6cf203b91c3f620ee0716ac0b23bcaf8267e015f21cd6683bdce169adf", "c91bc14bc62e294bbaf018e95590a9414e57a10fda640e895094a5e8b8259063", "10fed058af973ffce38492230d358699db13deae1f04b04194b9c7a9a39917f5", "93e23c1d702a79ddc9370073a65cfefb6c7902876efe221a41e37888e8652584", "030a23964ce2f625e3c5c7aae1a414b02464d348313f14e435d543264adb38c0", "6db086cba7918b5a38dbbdd67f4b3d24e7dd6fa0e5d61bfd49286e1435838a5d", "053b04e1293ba19a0a361c6458a8f074705273ffef1882bc7726cd7d5a2d7a19", "a937e8c52a535b9e0333e6f9d53e3c8a88f9235338fdce4aaafcb5903486679b", "b1e664e39bef5b3dd567bd9348d112fdf81810ecd822961625ba6c7bfba81dbd", "4e44aac92721c5446927a7f2a5e917c9cb16cd1fcf2738e54b227669d1db7fe7", "671d57690bb92ee8275b6fb5a9c36f7d73cebae6e8b2370031223601d5e0c901", "1d27eaa0942a61978ba837ec9756fbc8fc0b47b5e703e9fee364e661db90b36d", "a019bed1e2e19f393d567ebb5754ae5b06ea96e4101dfe3e5352a9ac3ed42b3d", "d6a1474d90596fe202774badc6f815012b0964094a552eb01291b5fb28250d0e", "bac1e74c86d2d6d5f79231751a2d16d3ab14bf025f66a2e01e8d02ced3bd3659", "ed6b3824221a434f3846d717c40a081eebf2142c7029bdf3087e3f22605de403", "5abb45f1491839a0720fbe1c91c79e2894ae32a334bf33b7c649a5e58b3e9eb7", "d6c0790ce00205814ead50bebe4948e00f40ed462f862089e84334c7730599b7", "36392a12e873b98a54ae1102dea71801ed7b3a848fae0aed4d9d19f01f62730a", "18b357482c0145bd430324ac2dd21814fa8597a34783461c328aa30ec636e9f6", "00fe77cb493a303907d4f70d90e407cefc50aff0d950e4125ab3c9797cc9ed6b", "8e91a1cf376f095449b8e46b7fecec67afafaae1169e1047c9adc8ea56d95de8", "bf8f45f96b23148c030eb37927bb3c95e12797e7e58d720f65e225620d018ea9", "a0f6beafed219bae0c9a3e102eb437413bdb43e4f47d5ac34146215239d2ed75", "73ffb6ffbc47e0c079a24f4cef1325536a21febc503a3b44d424a34c72bde016", "a482504a81a449698c4eecef41688077282c033675d1abe7631a1db5bd97dd1f", "30b96a0e5d8c5ef5451c256004dc7948942a1964d2dca176170ecb126ce632cb", "d1e5ed4a81c591cd31c875c22b586166f86b56d90a5afcfbb04a10c191339837", "25c251892399e0a393034adb294a447b1f0afc9cc190a7f7cf813057d87c66ec", "e8004a0c7bdef8ab5e0d77d90036c308137dacd6701620eeb1e7c416dd61abce", "e82d53da433de826af2ec5d62a4139363fbfd3deb75cdf6ad46bfe5cf9607c3d", "2d2c2086ea75c7783589bdb7f7686c395b61a862eaabd7d6a5b5ec1002d98530", "cfd5914f7dfd22d37769fc06e38ed75613ccfdf043383a16f1f89df10c50dd4e", "e29ad7431fc2c1cddd575c37097856bf9d50024b0444e198339b3a7cd81ae4d9", "8cd866a85085483857030b5b6dc6e52d2d90c15c7bcf692d83e8196d7833c79e", "569c0af3357e64fa626ec870f1109fac832316acb1534cbd8f0dce881f957efb", "2f78e74dd3c433e67bbed91bc0ac37a8731fa28e6614048856438ef20c8f92a0", "890f3f1c914e3e317a883fe2fef637c6c223ad9d6a8a6fe2744211e8a743d581", "3966072ff54c981b9f37dce6f32e86a0269906a17312027a718392d2b0e7d77a", "f9968eba94545a09077a45e7ca9109162821ad1b8d2710a4a7e77e3054a479c2", "fda0acb4e0a8b25b0defa8d5a1d474e140bb20317c8f5ff55f64a02f353377c5", "d04278cbffcb10cb67f55d6ad829302ba4825635261d0ace932b9f2753aec5ee", "259d9c52c59e6c9b38671e016b15b9de3ac8c3b00e7ce5f2812d925413381d63", "5de301d94cc9708e5c32ea740bc030761ca78fe5f3eb964bf4576b7d812c5064", "7849fd4fe5f268eddb773f467c852123c4a198e40d2824b02ce66b4123e93c3a", "373b90dd74af76df57f74d69c7793ffc4ac8c31eadf7e042ca46f08b56829414", "1bac26d91348b6d300c79a6d986dfcf5ad0f6a4dfaf09443501a7aca89071b9c", "a7992226e0da2976a4a82612cd12bb374901b37f9b8de46ac04f18ffb077c66e", "b60a31ab84da8f1623b71c393f2495ab0694e20102397486cde605a2b580b055", "1978e89d8b1506d978bab4d2a612f1009836a26ff4aef5046f6b43909b5b1872", "0e9e6ba902a7d110737ffc0ead82bfc8643a6c7db4b58535724d46048b2fbb03", "30ff2d724daba654b2bdfc976a547f3feff4da70365bf0b58004c7dbd4daf675", "39a4f50534eb2d6252ec69264e1a146e78648e4be595cb9cb1de0b50e1db32b9", "2f10189f28cc12430d4b00939d79e1fde0de421608e42a74816293b93e37d84e", "eaaaf979abcb3e681868357c73422958d568f4c1301df93017dc634319a26df7", "d96343e6813e8946e7583803cd296e73982d283ff9a4478817bf4c5ef8eb0496", "ab384f386dfe246f5bdc9cbd7f83d9dde8b795d1c4f6a93a47d02dabd8000ac8", "305c81137dba85a027a98d15534904c5ad3ee22e9fb9d3d9ea123f091988e4b7", "678c959b5ad643fc3461340543d055c1187343d7c0c52269e6948014c911e57b", "867ba8d9dea2e1c09635a777163abd915465b7f150296250d8dadeabcb6a0f33", "ed4bd440cfde230799256d429cb20c775a9f22f6dc392f27cebe649dd831c5e8", "0467a56308267651194977380e45a00d0957407f1ee7a2e7e77966ee23851f8b", "0d65887dbf61cf064e8f6f379f243d33c17ebfaddc51e3cabf28d24be5bae4b0", "a7cf54c785b57f0f494d38a1d05069a550a46bb006da61552e97c7bcf7d10db6", "a47f3ea99b020a43c7e1dfcf4f9127c7395bc9e3d324b7c2dd3f55e0a9420f3b", "c25556587b8afc31b510e732e9c5d1d11c80cc05dfc4bc47b95a31873a349a8e", "af0fea30c48b2901f8e974ea275da198c3b47b331510368b1655a67f974370a1", "e7874f784d0474e4a0f595d78264dfff42ff32552b7845d0e2aa150292446665", "040b0bba3bd0ea547627f94938e06833c7375a1f8ca9a3b1abc429a1e4a52a2c", "f4483991e87f8f3a573f1aa8ae1f14600b4047fc93104f416b7a45eff011a5ca", "565aeb5c434f6508510b3f765a21f03cf76dc838252fb28c59340fb3b03115c3", "5eed1df17bedbc8e9ba6e0d757ca23c0f4d91821813fb4a25b9043095f7c39b1", "01961f580576dcf4567f6e69940aeb0c9b7c02a9bb984d3de245a7c6d230bcdf", "d079012f119f4ff19b55ca7ea07f6772bedc224d0d7050959a546499ee50c99b", "1ced72c377b905c0d3808404e68a4cb6eddf3e366e13cf586842d04a18501504", "692bee2e21e36950abf5a2cefecbaa0f07550fb003d6a1a8fb5009fe5e1ef170", "856ab3020beb0b50f38760302d5110dae94096c505d2765d99169612fc330386", "7b83aad687c31d572499bc011a177f65077c18bb0c0a7f72a73b61779bf72d07", "88024da2decf5bbb4d0a241d4708240cdd4f81ec7bf0b1f188d0de057297e1a5", "041e4a68e928340037d9390d985cac9a8dd0ffab47b5d614d5ddbff57a4e046f", "0b0b61237271cece10d8b44d18e05054d4524d9dd96e894fbb3a7abb1b893fff", "cb526aa7325fbf3dcce1bda362a290141a8c4ba26b29d08c3a2ff7ec10a484ff", "33d566edcfce7f68bc778500387ee5d2957101bd3ee14473230221776dd4ab22", "7a3d8c8a8ef5de4e307bef7b9c1c54faa13f4d54980e5bbfd8b35375d958d1c7", "39305470301f396247a092c8a034ff82f8b89d613c91b0920635cb8808d94e02", "140f8e36efb1e08dfae45cb446bea2cead757c654e12513dcc81f3bf1dcea00e", "1ac668e55c7b4d0955fc34d1e3804d327b9733e9759d06d1acc4b46c78a446de", "1c756facd6be95d44fc015587f3731bae919b1cb867d4181d8de7a916d2dd64b", "f994be5802893f65d2671276011d3f5edcb6166c9f7ac5dc82b8f8af334d5127", "15d4b5defe7ee7ac07271787d13f5e46c642fe4bd010f77c981f0b1b21769b52", "0acfb984f6e813d69c5a2968c7901e58a402a73eaa61cb6e9e55fb9dcddf43b8", "df4c4018c4344b1c7013863475ef98f653300aa7206d2187630bb7947aade3c7", "07aed15a08810c563bd2b111cffd50d0ab00be8df1168c3b9fa0e9490653922e", "f72340bb3d23a7cc2ee89c9f06e31f60133c6383b1c80480fb1c5a1c5ed9d420", "3a8d0381f1f5b8bef32d2220914a35b8bb5ed1670cfca7ed8e3262e452d761b3", "e0ef1b65939f72063478f24861dd44a898a0bdeaf86d6f9ebfb06c2d8899214a", "b0625c19efa3261523a457ab21e80a17e2e429efd8c4f8733b05f11b2aa8e101", "0d001da3baa1f6ea78e351e9998d14c50b4a76be76f7a2ac2c14719f24d00dc2", "b3e3b6cf8df9ff130cc4ab41d963e4a932a9e3aba2bfbe2440842d59d4e82c44", "6e45b27b0e77509be6d177e0682949a6318aaa07242701f48e857aab0c4e6fc7", "b15165649520ffe5b8ffc5d9a9ef0b39e490f011fd4fec85a8faefd3679315ad", "b8554723d48814495bc3f37eccc14a0b863c5dbec31defe76ba54796da80d396", "a21c932632020ff5d80faee067474c6ed348ea7ea4756489a4039cc95f11254e", "e728a0ba1b2d21bb59b5fb9502bf4498ec8ffd71db3d840049bd391840b10645", "6f215728aae4cfe03341354577cdcf26c9093010716011a8ab14936780a712e6", "12b511ad68521ecc6f8f625ec8045aa35208342d1189b382457ed4d47787c4ed"};
    
        // Get the number of rows and columns in the matrix
        int rownum = dimen+10; //sizeof(inputdata)/sizeof(char*);
        int hexcharnum = 0;
        while (inputdata[0][hexcharnum]!='\0') {
            hexcharnum++;
        }
        int colnum = (hexcharnum)*4; // 4 bits per hexa-character
        
        
        // splitting parts of the strings into arrays of unsigned long
        int lastarr_size = hexcharnum%16;
        int arr_count = (hexcharnum/16)+(lastarr_size?1:0); // the number of arrays needed
        unsigned long arr[arr_count][rownum]; // 2D array
        
        for (int i = 0, post = 0; i<arr_count; i++, post = post+16) {
            for (int j = 0; j<rownum; j++) {
                char t1[17];
                strncpy(t1, inputdata[j]+post, 16);
                t1[16] = '\0';
                arr[i][j] = strtoul(t1, NULL, 16);
                if (i==arr_count-1) {                       // if last array, left shift appropriately
                    arr[i][j]= arr[i][j]<<((16-(hexcharnum%16))*4);
                }
            }
        }
        
        
        // XOR the values
        unsigned long checkbit = 1, movenum = 64;
        unsigned long curcol = (arr_count*NUM_BITS_IN_TYPE)-1;
        unsigned long temprow[arr_count][1];
        int curarr = 0;
        for (int rowdone = 0, pivrow = 0; rowdone < rownum; rowdone++) {
            for (int currow = pivrow; currow < rownum; currow++) {
                if (arr[curarr][currow] & (checkbit<<(curcol%movenum))) {
                    for (int k = 0; k<arr_count; k++) {
                        temprow[k][0] = arr[k][currow];
                        arr[k][currow] = arr[k][pivrow];
                    }
                    for (int xorrow = 0; xorrow < rownum; xorrow++) { // if Gaussian-Jacob, start xorrow at 0, else at pivrow+1
                        if (arr[curarr][xorrow] & (checkbit<<(movenum-rowdone-1))) {
                            for (int k = 0; k<arr_count; k++) {
                                arr[k][xorrow]=arr[k][xorrow]^temprow[k][0];
                            }
                        }
                    }
                    for (int k = 0; k<arr_count; k++) {
                        arr[k][pivrow] = temprow[k][0];
                    }
                    pivrow++;
                    break;
                }
            }
            if (!(curcol%NUM_BITS_IN_TYPE)) {
                curarr++;
            }
            curcol--;
        }
        
        
        // extract & export
        
        char **orderedIds;
        
        orderedIds = malloc(rownum * sizeof(char*));
        for (int i = 0; i < rownum; i++)
            orderedIds[i] = malloc((hexcharnum+1) * sizeof(char));
        for (int i = 0; i < rownum; i++) {
            for (int j = 0, pos = 0; j < arr_count; j++){
                char* temp = malloc(16);
                sprintf(temp, "%016lx\n", arr[j][i]);
                strcpy(orderedIds[i]+pos, temp);
                pos = pos+16;
            }
            orderedIds[i][hexcharnum] = '\0';
        }
        
        char* fileout[10];
        sprintf(fileout, "%d_%dout.txt", dimen,iter);
        FILE *f = fopen(fileout, "w");
        if (f == NULL)
        {
            printf("Error opening file!\n");
            exit(1);
        }
        for (int i = 0; i<(rownum-10); i++) {
            //printf("%s\n", orderedIds[i]+(hexcharnum/2));
            fprintf(f, "%s\n", orderedIds[i]+(hexcharnum/2));
        }
        
        iter = iter+1;
        
    }
    return 0;
}