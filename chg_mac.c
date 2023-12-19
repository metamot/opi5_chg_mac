#include <stdio.h>
#include <stdint.h>
int main(int argc, char *argv[]) {
  FILE* fp=NULL;
  int i;
  size_t sz;
  uint8_t b[6]={0xfe,0xdc,0xab,0x12,0x34,0x56};
  unsigned int z[6];
  printf("USAGE Read&Print MAC from spi-image-file: %s\n",argv[0]);
  printf("USAGE Write MAC to spi-image-file       : %s xx:xx:xx:xx:xx:xx\n",argv[0]);
  if(argc>2) { fprintf(stderr,"ERROR: To many args!\n"); return -1; }
  if(argc==1) {
    printf("Read MAC from spi.img file...\n");
    fp=fopen("spi.img", "r");
    if(fp==NULL) { fprintf(stderr,"ERROR: Can't open spi.img file!\n"); return -1; }
    fseek(fp,0x380206,SEEK_SET);
    fread(b,sizeof b[0], 6, fp);
    printf("[0x380206]: ");
    for(i=0;i<5;i++) printf("%02x:",b[i]);
    printf("%02x\n",b[5]);
    fseek(fp,0x381206,SEEK_SET);
    fread(b,sizeof b[0], 6, fp);
    printf("[0x381206]: ");
    for(i=0;i<5;i++) printf("%02x:",b[i]);
    printf("%02x\n",b[5]);
  }
  if(argc==2) {
    i=sscanf(argv[1],"%02x:%02x:%02x:%02x:%02x:%02x",&z[0],&z[1],&z[2],&z[3],&z[4],&z[5]);
    if(i!=6) { fprintf(stderr,"ERROR: Wrong input! Must be 6 hex-bytes delimited with ':'\n"); return -1; }
    printf("Ok. You entered %d numbers.\n",i);
    printf("New MAC: ");
    for(i=0;i<6;i++) b[i]=(uint8_t)z[i];
    for(i=0;i<5;i++) printf("%02x:",b[i]);
    printf("%02x\n",b[5]);
    fp=fopen("spi.img", "r+");
    if(fp==NULL) { fprintf(stderr,"ERROR: Can't open spi.img file!\n"); return -1; }
    fseek(fp,0x380206,SEEK_SET);
    fwrite(b,sizeof b[0], 6, fp);
    fseek(fp,0x381206,SEEK_SET);
    fwrite(b,sizeof b[0], 6, fp);
    printf("DONE! You need to update spi manually with this command... \n");
    printf("$ sudo dd if=spi.img of=/dev/mtdblock0 bs=1M conv=notrunc\n");
    printf("Please be patient. Spi update lasts about 5 minutes.\n");
  }
  if(fp!=NULL) fclose(fp);
  return 0;
}

