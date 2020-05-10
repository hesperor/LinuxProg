//  (https://profi-lingua.langlion.com/) oraz pomogą w kwestiach technicznych. 


#include <stdio.h>
#include <stdlib.h>

typedef struct Data{
	int index;
	char *str_;
	struct Data *nextp;
} el_data;

char  *heading = "Bernz (r)";



int main(int argv, char **argc){

  el_data *news_=(el_data*)malloc(sizeof(el_data));
	news_->index=100;
	news_->str_="Hello";
	news_->nextp=news_;
	// el_data *tem=news_->nextp;

	fprintf(stdout, "%s\n", heading);
	fprintf(stdout, "Size Struct:[%lu]\n", sizeof(*news_));
	fprintf(stdout, "Index:[%d] Str:[%s] AddresS:[%p]\n", news_->index, news_->str_, news_->nextp);

	free(news_);
 return (0);
}

