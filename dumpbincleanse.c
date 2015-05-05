#include <stdio.h>
#include <assert.h>

#define buffer_len (8192)
static char buffer[buffer_len];

int core(char *in, char *out){
	FILE *infile = fopen(in, "r"), *outfile = fopen(out, "w");
	unsigned fluff_length = 26, wasted_lines = 19;

	if(!(infile&&outfile)){
		if(infile){
			fclose(infile);
		}
		else{
			fputs("Could not open input file:", stderr);
			fputs(in, stderr);
		}
		if(outfile){
			fclose(outfile);
		}
		else{
			fputs("Could not open output file:", stderr);
			fputs(out, stderr);
		}
		
		return 0;
	}
	
	fputs("EXPORTS\n", outfile);
	puts("Gathering Exports...");
	
	while(--wasted_lines!=0){
		while(fgetc(infile)!='\n'){
			if(feof(infile)){
				fputs("EOF in infile before enough wasted lines were found.\n", stderr);
				return 0;
			}
		}
	}
	
	puts("Beginning read...");
	
	/* Steals the initial char that the 'Blank line' fgetc would do. */
	fgetc(infile),fgetc(infile);
	
	while(!feof(infile)){
		unsigned skip = 0, cursor = 0;
			
		/* cut out the address info. We'll just push it into the buffer, since it's full of garbage anyway */
		fread(buffer, fluff_length-1, 1, infile);
		
		/* copy the symbol name to the buffer. */
		do{
			assert(cursor<buffer_len);
			buffer[cursor] = fgetc(infile);
			if(buffer[cursor]=='=')
				skip = 1;
		} while((buffer[cursor++]!='\n') && (!feof(infile)));
		
		/* Blank line */
		if(fgetc(infile)=='\n')
			break;
		
		if(!skip){
			/* Null-term the buffer and write it to the outfile. */
			buffer[cursor] = 0;
			fputs(buffer, outfile);
		}
	}
	
	fclose(outfile);
	
	return 1;
	
}

int main(int argc, char *argv[]){
	char * outfile, *infile;
	if(argc<2){
		fputs("Usage: dumpbincleanse <infile> [outfile]", stderr);
		return 0;
	}
	
	infile = argv[1];
	
	if(argc<3)
		outfile = "dumpbincleanse.out";
	else
		outfile = argv[2];
	
	return core(infile, outfile);
	
}