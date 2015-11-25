//gcc -o simple simple.c `pkg-config --libs --cflags gtk+-2.0`

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <gtk/gtk.h>

char data_user[50];
const char *port_info;
const char *host_info;
int sockfd;

void client()
{
    int portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    portno = atoi(port_info);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(host_info);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
}

void refresh_data(char data_user[])
{
	int q;
  for(q=0;q<23;q++)
	data_user[q]=' ';
  for(q=23;q<46;q++)
  {
  	if(q%2==1) data_user[q]='n';
  	else data_user[q]=' ';
  }
  data_user[46]='\0';
}

void submit_date(GtkWidget *widget, gpointer entry2)
{
	GtkWidget *window,*label,*frame;
	int i,k=0,error;
	const char *date_c;
	error=0;
	date_c = gtk_entry_get_text (GTK_ENTRY(entry2));
	if(strlen(date_c)!=10) error=1;
	if(error)
	{
		window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  		gtk_window_set_title(GTK_WINDOW(window), "ERROR");
 		gtk_window_set_default_size(GTK_WINDOW(window), 230, 150);
  		gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  		
  		frame = gtk_fixed_new();
  		gtk_container_add(GTK_CONTAINER(window), frame);
  		
  		label = gtk_label_new("                ***ERROR***\nGIVE A VALID DATE(dd-mm-yyyy)!!!");
  		gtk_fixed_put(GTK_FIXED(frame), label, 10, 70);
  		
  		gtk_widget_show(label);
  		gtk_widget_show_all(window);

  		g_signal_connect_swapped(G_OBJECT(window), "destroy",
      			G_CALLBACK(gtk_main_quit), NULL);

  		gtk_main();
	}
	else
	{
		for(i=0;i<strlen(date_c);i++)
		{
			if(i==2 || i==5) continue;
			data_user[k] = date_c[i];
			k++;
		}
		data_user[k]=' ';
		printf("date=%s\n",date_c);
		//send to server here
	}
}

void submit_cap(GtkWidget *widget, gpointer entry1)
{
	GtkWidget *window,*label,*frame;
	int i,k=9,error;
	const char *cap_c;
	error=0;
	cap_c = gtk_entry_get_text (GTK_ENTRY(entry1));
	if(strlen(cap_c)==0 || strlen(cap_c) > 4) error=1;
	if(error)
	{
		window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  		gtk_window_set_title(GTK_WINDOW(window), "ERROR");
 		gtk_window_set_default_size(GTK_WINDOW(window), 230, 150);
  		gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  		
  		frame = gtk_fixed_new();
  		gtk_container_add(GTK_CONTAINER(window), frame);
  		
  		label = gtk_label_new("                ***ERROR***\nCAPACITY IS TOO LOW OR HIGH!!");
  		gtk_fixed_put(GTK_FIXED(frame), label, 10, 70);
  		
  		gtk_widget_show(label);
  		gtk_widget_show_all(window);

  		g_signal_connect_swapped(G_OBJECT(window), "destroy",
      			G_CALLBACK(gtk_main_quit), NULL);

  		gtk_main();
	}
	else
	{
		for(i=0;i<4-strlen(cap_c);i++)
		{
			data_user[k] = '0';
			k++;
		}
		for(i=0;i<strlen(cap_c);i++)
		{
			data_user[k] = cap_c[i];
			k++;
		}
		data_user[k]=' ';
		printf("capacity=%s\n",cap_c);
	}
}

void time_from(GtkWidget *widget, gpointer arbit)
{ 
  	char *text =  gtk_combo_box_get_active_text(GTK_COMBO_BOX(widget));
  	data_user[14] = text[0];
  	data_user[15] = text[1];
  	printf("text=%s\n",text);
	
}

void time_from_mt(GtkWidget *widget, gpointer arbit)
{ 
  	char *text =  gtk_combo_box_get_active_text(GTK_COMBO_BOX(widget));
  	data_user[16] = text[0];
  	data_user[17] = text[1];
  	printf("text=%s\n",text);
	
}

void time_to(GtkWidget *widget, gpointer arbit)
{ 
  	char *text =  gtk_combo_box_get_active_text(GTK_COMBO_BOX(widget));
  	data_user[18] = text[0];
  	data_user[19] = text[1];
  	printf("text!!=%s\n",text);
	
}

void time_to_mt(GtkWidget *widget, gpointer arbit)
{ 
  	char *text =  gtk_combo_box_get_active_text(GTK_COMBO_BOX(widget));
  	data_user[20] = text[0];
  	data_user[21] = text[1];
  	data_user[22] = ' ';
  	printf("text!!=%s\n",text);
}

void w_brd(GtkWidget *widget, gpointer arbit)
{
	static int i;
	if(i%2 == 0)
	{
		data_user[23] = 'y';//for white board
	}
	if(i%2 == 1)
	{
		data_user[23] = 'n';//---do----
	}
	data_user[24] = ' ';
	printf("%d\n",i);
	i++;
}

void proj(GtkWidget *widget, gpointer arbit)
{
	static int i;
	if(i%2 == 0)
	{
		data_user[25] = 'y';//for projector
	}
	if(i%2 == 1)
	{
		data_user[25] = 'n';//---do----
	}
	data_user[26] = ' ';
	printf("%d\n",i);
	i++;
}

void proj_mic(GtkWidget *widget, gpointer arbit)
{ 
  	char *text =  gtk_combo_box_get_active_text(GTK_COMBO_BOX(widget));
  	if(text[0]=='y' && data_user[25]=='y')
  		data_user[27] = 'y';
  	else
  		data_user[27] = 'n';
  	data_user[28] = ' ';
}

void lcd(GtkWidget *widget, gpointer arbit)
{
	static int i;
	if(i%2 == 0)
	{
		data_user[29] = 'y';//for lcd
	}
	if(i%2 == 1)
	{
		data_user[29] = 'n';//---do----
	}
	data_user[30] = ' ';
	printf("%d\n",i);
	i++;
}

void sound_sys(GtkWidget *widget, gpointer arbit)
{
	static int i;
	if(i%2 == 0)
	{
		data_user[31] = 'y';//for sound system
	}
	if(i%2 == 1)
	{
		data_user[31] = 'n';//---do----
	}
	data_user[32] = ' ';
	printf("%d\n",i);
	i++;
}

void sound_sys_mic(GtkWidget *widget, gpointer arbit)
{ 
  	char *text =  gtk_combo_box_get_active_text(GTK_COMBO_BOX(widget));
  	if(text[0]=='y' && data_user[31]=='y')
  		data_user[33] = 'y';
  	else
  		data_user[33] = 'n';
  	data_user[34] = ' ';
}

void aud_rec(GtkWidget *widget, gpointer arbit)
{
	static int i;
	if(i%2 == 0)
	{
		data_user[35] = 'y';//for sound system
	}
	if(i%2 == 1)
	{
		data_user[35] = 'n';//---do----
	}
	data_user[36] = ' ';
	printf("%d\n",i);
	i++;
}

void aud_rec_mic(GtkWidget *widget, gpointer arbit)
{ 
  	char *text =  gtk_combo_box_get_active_text(GTK_COMBO_BOX(widget));
  	if(text[0]=='y' && data_user[35]=='y')
  		data_user[37] = 'y';
  	else
  		data_user[37] = 'n';
  	data_user[38] = ' ';
}

void vid_rec(GtkWidget *widget, gpointer arbit)
{
	static int i;
	if(i%2 == 0)
	{
		data_user[39] = 'y';//for sound system
	}
	if(i%2 == 1)
	{
		data_user[39] = 'n';//---do----
	}
	data_user[40] = ' ';
	printf("%d\n",i);
	i++;
}

void vid_rec_mic(GtkWidget *widget, gpointer arbit)
{ 
  	char *text =  gtk_combo_box_get_active_text(GTK_COMBO_BOX(widget));
  	if(text[0]=='y' && data_user[39]=='y')
  		data_user[41] = 'y';
  	else
  		data_user[41] = 'n';
  	data_user[42] = ' ';
}

void vid_rec_cam(GtkWidget *widget, gpointer arbit)
{ 
  	char *text =  gtk_combo_box_get_active_text(GTK_COMBO_BOX(widget));
  	if(text[0]=='y' && data_user[39]=='y')
  		data_user[43] = 'y';
  	else
  		data_user[43] = 'n';
  	data_user[44] = ' ';
}

void air_cond(GtkWidget *widget, gpointer arbit)
{
	static int i;
	if(i%2 == 0)
	{
		data_user[45] = 'y';//for air_cond
	}
	if(i%2 == 1)
	{
		data_user[45] = 'n';//---do----
	}
	data_user[46] = '\0';
	printf("%d\n",i);
	i++;
}

void display_admin_reqid(char reqid[])
{
  char message[50]={"YOUR HIGH PRIORITY REQUEST ID IS:"};
  strcat(message,reqid);printf("message=%s\n",message);
  
  GtkWidget *label;
  GtkWidget *window;
  GtkWidget *frame;
  
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 450, 400);
  gtk_window_set_title(GTK_WINDOW(window), "REQUEST ID");

  frame = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(window), frame);
  
  label = gtk_label_new(message);
  gtk_fixed_put(GTK_FIXED(frame), label, 80, 180);
  
  gtk_widget_show(label);
  gtk_widget_show_all(window);
  
  g_signal_connect(window, "destroy",
      G_CALLBACK (gtk_main_quit), NULL);
      
  gtk_main();
  
  return;
}

int find_lines_admin(char filename[])
{
	FILE* myfile = fopen(filename, "r");
	int ch, number_of_lines = 0;

	do 
	{
    	ch = fgetc(myfile);
    	if(ch == '\n')
        	number_of_lines++;
	} while (ch != EOF);

	// last line doesn't end with a new line!
	// but there has to be a line at least before the last line
	if(ch != '\n' && number_of_lines != 0) 
    	number_of_lines++;

	fclose(myfile);

	return(number_of_lines);
}

char admin_file()
{
	printf(">>>1\n");
	char reqid[15];
	int i,k=0,lines;
	char date[15];
	char lin[3];
	char filename[20]={"admin/"};
	char data_wr[50];
	for(i=0;i<8;i++)
	{
		date[k] = data_user[i];
		k++;
	}
	date[k]='\0';printf("date=%s\n",date);
	strcat(filename,date);printf("filename=%s\n",filename);
	data_wr[0]='n';
	data_wr[1]=' ';
	data_wr[2]='\0';
	strcat(data_wr,data_user);printf("data_wr=%s\n",data_wr);
	FILE *fp;
	fp = fopen(filename,"a");
	fprintf(fp,"%s\n",data_wr);
	fclose(fp);
	lines = find_lines_admin(filename)-1;
	sprintf(lin,"%d",lines);
	if(strlen(lin) == 1) {date[8]='a';date[9]='0';date[10]=lin[0];date[11]='\0';}
	if(strlen(lin) == 2) {date[8]='a';date[9]=lin[0];date[10]=lin[1];date[11]='\0';}
	strcpy(reqid,date);printf("reqid=%s\n",reqid);
	display_admin_reqid(reqid);

}

void display_reqid(int i, char buffer[])
{
  char message[50];
  
  GtkWidget *label,*label1,*label2,*label3;
  GtkWidget *window;
  GtkWidget *frame;
  GtkWidget *high;
  
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 450, 400);
  gtk_window_set_title(GTK_WINDOW(window), "REQUEST ID");

  frame = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(window), frame);
  
  if(i==-1)
  {
  	label3 = gtk_label_new("REQUEST NOT ACCEPTED");
  	gtk_fixed_put(GTK_FIXED(frame), label3, 130, 180);
  	
  	high = gtk_button_new_with_label("PLACE HIGH PRIORITY");
  	gtk_widget_set_size_request(high, 160, 30);
  	gtk_fixed_put(GTK_FIXED(frame), high, 130, 200);
  }
  else
  {
  	label = gtk_label_new("REQUEST UNDER PROCESS\n");
  	gtk_fixed_put(GTK_FIXED(frame), label, 130, 180); 
  	label1 = gtk_label_new("REQUEST ID:");
  	gtk_fixed_put(GTK_FIXED(frame), label1, 130, 200); 
  	label2 = gtk_label_new(buffer);
  	gtk_fixed_put(GTK_FIXED(frame), label2, 215, 200); printf(">>>1\n");
  }
  if(i!=-1)
  {gtk_widget_show(label);
  gtk_widget_show(label1);
  gtk_widget_show(label2);printf(">>>2\n");}
  else
  	gtk_widget_show(label3);
  gtk_widget_show_all(window);
  
  printf(">>>3\n");g_signal_connect(window, "destroy",
      G_CALLBACK (gtk_main_quit), NULL);
      
  if(i==-1){g_signal_connect(high, "clicked", 
      G_CALLBACK(admin_file), NULL);}
  printf(">>>5\n");    
  gtk_main();
  
  return;
}

void send_data(GtkWidget *widget, gpointer arbit)
{
	int n,i;
	char buffer[256];
	char reqid[12];
	printf("data_user= %s \n",data_user);
	n = write(sockfd,data_user,strlen(data_user));
	if(n<0)
	 error("ERROR writing to socket");
	//read his reqid and dispaly,and then finally exit after 10seconds
	bzero(buffer,256);
	n = read(sockfd,buffer,255);
    	if (n < 0) 
         error("ERROR reading from socket");
        printf("buffer=%s\n",buffer);
        if(buffer[0]=='h')
        	{display_reqid(-1,buffer);}
        else
        {
        	for(n=0;n<8;n++)
        		reqid[n]=data_user[n];
        	for(i=0;i<3-strlen(buffer);i++)
        	{
        		reqid[n]='0';
        		n++;
        	}
        	for(i=0;i<strlen(buffer);i++)
        	{
        		reqid[n]=buffer[i];
        		n++;
        	}
        	reqid[n]='\0';printf("reqid=%s\n",reqid);
        	display_reqid(1,reqid);
        }
    	printf("buffer=%s\n",buffer);
    	//sleep(10);
    	//exit(EXIT_SUCCESS);
}

void book_gui(GtkWidget *widget, gpointer label)
{
  GtkWidget *window;
  GtkWidget *frame;
  GtkWidget *submit,*back;
  GtkWidget *label1,*label2,*label3,*label4,*label5,*label6,*label7,*label8;
  GtkWidget *entry1,*entry2;
  GtkWidget *combo,*combo1,*combo2,*combo3,*combo4,*combo5,*combo6,*combo7,*combo8;
  GtkWidget *att1,*att2,*att3,*att4,*att5,*att6,*att7;
  
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 650, 600);
  gtk_window_set_title(GTK_WINDOW(window), "BOOK YOUR ROOM");

  frame = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(window), frame);
  
  label7 = gtk_label_new("DATE");
  label8 = gtk_label_new("(dd-mm-yyyy)");
  gtk_fixed_put(GTK_FIXED(frame), label7, 210, 100);
  gtk_fixed_put(GTK_FIXED(frame), label8, 440, 100);
  entry2 = gtk_entry_new();
  gtk_fixed_put(GTK_FIXED(frame), entry2, 280, 95);
  
  label1 = gtk_label_new("CAPACITY");
  gtk_fixed_put(GTK_FIXED(frame), label1, 210, 135);
  
  entry1 = gtk_entry_new();
  gtk_fixed_put(GTK_FIXED(frame), entry1, 280, 130);
  
  label2 = gtk_label_new("TIME SLOT");
  gtk_fixed_put(GTK_FIXED(frame), label2, 210, 170);
  label3 = gtk_label_new("from");
  gtk_fixed_put(GTK_FIXED(frame), label3, 300, 170);
  
  combo = gtk_combo_box_new_text();
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "00");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "01");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "02");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "03");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "04");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "05");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "06");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "07");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "08");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "09");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "10");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "11");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "12");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "13");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "14");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "15");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "16");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "17");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "18");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "19");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "20");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "21");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "22");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "23");
  gtk_fixed_put(GTK_FIXED(frame), combo, 335, 165);
  
  label7 = gtk_label_new(":");
  gtk_fixed_put(GTK_FIXED(frame), label7, 390, 170);
  
  combo7 = gtk_combo_box_new_text();
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo7), "00");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo7), "30");
  gtk_fixed_put(GTK_FIXED(frame), combo7, 395, 165);
    
  label4 = gtk_label_new("to");
  gtk_fixed_put(GTK_FIXED(frame), label4, 470, 170);
  
  combo1 = gtk_combo_box_new_text();
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo1), "00");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo1), "01");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo1), "02");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo1), "03");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo1), "04");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo1), "05");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo1), "06");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo1), "07");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo1), "08");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo1), "09");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo1), "10");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo1), "11");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo1), "12");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo1), "13");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo1), "14");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo1), "15");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo1), "16");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo1), "17");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo1), "18");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo1), "19");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo1), "20");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo1), "21");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo1), "22");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo1), "23");
  gtk_fixed_put(GTK_FIXED(frame), combo1, 490, 165);
  
  label8 = gtk_label_new(":");
  gtk_fixed_put(GTK_FIXED(frame), label8, 545, 170);
  
  combo8 = gtk_combo_box_new_text();
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo8), "00");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo8), "30");
  gtk_fixed_put(GTK_FIXED(frame), combo8, 550, 165);
    
  att1 = gtk_check_button_new_with_label("WHITE BOARD");
  //gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check), TRUE);
  GTK_WIDGET_UNSET_FLAGS(att1, GTK_CAN_FOCUS);
  gtk_fixed_put(GTK_FIXED(frame), att1, 210, 200);
  
  att2 = gtk_check_button_new_with_label("PROJECTOR");
  GTK_WIDGET_UNSET_FLAGS(att2, GTK_CAN_FOCUS);
  gtk_fixed_put(GTK_FIXED(frame), att2, 210, 225);
  
  label5 = gtk_label_new("Audio facility required");
  gtk_fixed_put(GTK_FIXED(frame), label5, 230, 245);
  
  combo2 = gtk_combo_box_new_text();
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo2), "yes");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo2), "no");
  
  gtk_fixed_put(GTK_FIXED(frame), combo2, 403, 240);
  
  att3 = gtk_check_button_new_with_label("LCD Display");
  GTK_WIDGET_UNSET_FLAGS(att3, GTK_CAN_FOCUS);
  gtk_fixed_put(GTK_FIXED(frame), att3, 210, 270);
  
  att4 = gtk_check_button_new_with_label("SOUND SYSTEM");
  GTK_WIDGET_UNSET_FLAGS(att4, GTK_CAN_FOCUS);
  gtk_fixed_put(GTK_FIXED(frame), att4, 210, 295);
  
  label5 = gtk_label_new("Microphones for audience");
  gtk_fixed_put(GTK_FIXED(frame), label5, 230, 315);
  
  combo3 = gtk_combo_box_new_text();
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo3), "yes");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo3), "no");
  
  gtk_fixed_put(GTK_FIXED(frame), combo3, 403, 310);
  
  att5 = gtk_check_button_new_with_label("AUDIO RECORDING FACILITY");
  GTK_WIDGET_UNSET_FLAGS(att5, GTK_CAN_FOCUS);
  gtk_fixed_put(GTK_FIXED(frame), att5, 210, 345);
  
  label6 = gtk_label_new("Microphones for audience");
  gtk_fixed_put(GTK_FIXED(frame), label6, 230, 365);
  
  combo4 = gtk_combo_box_new_text();
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo4), "yes");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo4), "no");
  
  gtk_fixed_put(GTK_FIXED(frame), combo4, 403, 362);
  
  att6 = gtk_check_button_new_with_label("VIDEO RECORDING FACILITY");
  GTK_WIDGET_UNSET_FLAGS(att6, GTK_CAN_FOCUS);
  gtk_fixed_put(GTK_FIXED(frame), att6, 210, 395);
  
  label6 = gtk_label_new("Microphones for audience");
  gtk_fixed_put(GTK_FIXED(frame), label6, 230, 415);
  
  combo5 = gtk_combo_box_new_text();
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo5), "yes");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo5), "no");
  
  gtk_fixed_put(GTK_FIXED(frame), combo5, 403, 412);
  
  label6 = gtk_label_new("Camera for audience");
  gtk_fixed_put(GTK_FIXED(frame), label6, 230, 445);
  
  combo6 = gtk_combo_box_new_text();
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo6), "yes");
  gtk_combo_box_append_text(GTK_COMBO_BOX(combo6), "no");
  
  gtk_fixed_put(GTK_FIXED(frame), combo6, 403, 442);
  
  att7 = gtk_check_button_new_with_label("AIR-CONDITIONING");
  GTK_WIDGET_UNSET_FLAGS(att7, GTK_CAN_FOCUS);
  gtk_fixed_put(GTK_FIXED(frame), att7, 210, 470);
  
  submit = gtk_button_new_with_label("SUBMIT");
  gtk_widget_set_size_request(submit, 100, 25);
  gtk_fixed_put(GTK_FIXED(frame), submit, 520, 570);
  
  back = gtk_button_new_with_label("BACK");
  gtk_widget_set_size_request(back, 100, 25);
  gtk_fixed_put(GTK_FIXED(frame), back, 30, 570);
  
  gtk_widget_show(label1);
  gtk_widget_show(entry1);
  gtk_widget_show_all(window);

  g_signal_connect(window, "destroy",
      G_CALLBACK (gtk_main_quit), NULL);
       
  g_signal_connect(G_OBJECT(combo), "changed", 
      G_CALLBACK(time_from), NULL);
  
  g_signal_connect(G_OBJECT(combo7), "changed", 
      G_CALLBACK(time_from_mt), NULL);
  
  g_signal_connect(G_OBJECT(combo1), "changed", 
      G_CALLBACK(time_to), NULL);
      
  g_signal_connect(G_OBJECT(combo8), "changed", 
      G_CALLBACK(time_to_mt), NULL);
      
  g_signal_connect(att1, "clicked", 
      G_CALLBACK(w_brd), NULL);
      
  g_signal_connect(att2, "clicked", 
      G_CALLBACK(proj), NULL);
      
  g_signal_connect(G_OBJECT(combo2), "changed", 
      G_CALLBACK(proj_mic), NULL);
      
  g_signal_connect(att3, "clicked", 
      G_CALLBACK(lcd), NULL);
  
  g_signal_connect(att4, "clicked", 
      G_CALLBACK(sound_sys), NULL);
  
  g_signal_connect(G_OBJECT(combo3), "changed", 
      G_CALLBACK(sound_sys_mic), NULL);
  
  g_signal_connect(att5, "clicked", 
      G_CALLBACK(aud_rec), NULL);
      
  g_signal_connect(G_OBJECT(combo4), "changed", 
      G_CALLBACK(aud_rec_mic), NULL);
  
  g_signal_connect(att6, "clicked", 
      G_CALLBACK(vid_rec), NULL);
      
  g_signal_connect(G_OBJECT(combo5), "changed", 
      G_CALLBACK(vid_rec_mic), NULL);
  
  g_signal_connect(G_OBJECT(combo6), "changed", 
      G_CALLBACK(vid_rec_cam), NULL);
  
  g_signal_connect(att7, "clicked", 
      G_CALLBACK(air_cond), NULL);
  
  g_signal_connect(submit, "clicked", 
      G_CALLBACK(submit_date), entry2);
  
  g_signal_connect(submit, "clicked", 
      G_CALLBACK(submit_cap), entry1);
      
  g_signal_connect(submit, "clicked", 
      G_CALLBACK(send_data), entry1);
  
  g_signal_connect(back, "clicked", 
      G_CALLBACK(gtk_main_quit), NULL);
  
  gtk_main();

  return;
  //count++;

  //sprintf(buf, "%d", count);
  //gtk_label_set_text(label, buf);
}

void display_cancel(char buffer[])
{
  GtkWidget *label;
  GtkWidget *window;
  GtkWidget *frame;
  
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 450, 400);
  gtk_window_set_title(GTK_WINDOW(window), "REQUEST CANCELLED");

  frame = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(window), frame);
  
  label = gtk_label_new(buffer);
  gtk_fixed_put(GTK_FIXED(frame), label, 130, 180);
  	 
  gtk_widget_show(label);
  gtk_widget_show_all(window);
  
  g_signal_connect(window, "destroy",
      G_CALLBACK (gtk_main_quit), NULL);
      
  gtk_main();
  
  return;
}

void cancel_c(GtkWidget *widget, gpointer entry1)
{
	int n;
	char buffer[256];
	const char *reqid;
	reqid = gtk_entry_get_text (GTK_ENTRY(entry1));
	printf("reqid=%s\n",reqid);
	strcat(reqid,"c");
	//send reqid to server here for cancel || call cancel function here
	n = write(sockfd,reqid,strlen(reqid));
	if(n<0)
	 error("ERROR writing to socket");
	//read his reqid and dispaly,and then finally exit after 10seconds
	bzero(buffer,256);
	n = read(sockfd,buffer,255);
    	if (n < 0) 
         error("ERROR reading from socket");
    	//dispaly shall be done here
    	display_cancel(buffer);
    	printf("%s\n",buffer);
    	//sleep(10);
    	//exit(EXIT_SUCCESS);
}

void cancel_gui(GtkWidget *widget, gpointer label)
{
  GtkWidget *window;
  GtkWidget *frame;
  GtkWidget *label1;
  GtkWidget *cancel;
  GtkWidget *entry1;
    
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 650, 600);
  gtk_window_set_title(GTK_WINDOW(window), "CANCEL REQUEST");

  frame = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(window), frame);

  label1 = gtk_label_new("REQUEST ID");
  gtk_fixed_put(GTK_FIXED(frame), label1, 210, 250);
  
  entry1 = gtk_entry_new();
  gtk_fixed_put(GTK_FIXED(frame), entry1, 300, 245);
  
  cancel = gtk_button_new_with_label("CANCEL REQUEST");
  gtk_widget_set_size_request(cancel, 160, 30);
  gtk_fixed_put(GTK_FIXED(frame), cancel, 270, 280);
  
  gtk_widget_show_all(window);
  
  g_signal_connect(window, "destroy",
      G_CALLBACK (gtk_main_quit), NULL);
      
  g_signal_connect(cancel, "clicked", 
      G_CALLBACK(cancel_c), entry1);
  
  gtk_main();
  
  return;
  
  //count--;
  //sprintf(buf, "%d", count);
  //gtk_label_set_text(label, buf);
}

void display_status(char buffer[])
{
  printf("here\n");
  char message[50],message1[50],temp1[50],temp2[50],temp3[50];
  int h,h1,h2;
  //implement proper clock and time here
  
  GtkWidget *label,*label1,*label2;
  GtkWidget *window;
  GtkWidget *frame;
  
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 450, 400);
  gtk_window_set_title(GTK_WINDOW(window), "REQUEST STATUS");

  frame = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(window), frame);
  
  //char A[0]='a','c','n' A[1],A[2],A[3]=room no 8 len time slot
  if(buffer[strlen(buffer)-1]=='n')
  {
  	if(buffer[0] == 'n')
  		strcpy(message,"REQUEST UNDER PROCESS");
  	else if(buffer[0] == 'c')
  		strcpy(message,"REQUEST NOT APPROVED");
  	else if(buffer[0] == 'a')
  		strcpy(message,"REQUEST APPROVED BY ADMIN");
  	
  	label = gtk_label_new(message);
  	gtk_fixed_put(GTK_FIXED(frame), label, 130, 180);
  	gtk_widget_show(label);
  }
  
  else
  {
  	//@ later stage stage checking will be changed and buffer will have to be parsed to find details of room,time slot
  	//char A[0]='a','c','n' A[1],A[2],A[3]=room no 8 len time slot
  	printf(">>>1 buffer=%s\n",buffer);
  	if(buffer[0] == 'n' || buffer[0] == 'a')
  	{
  		printf("inside\n");
  		label = gtk_label_new("REQUEST APPROVED");
  		strcpy(message,"ROOM NO:");
  		h = strlen(message);printf("@@\n");
  		for(h1=0;h1<3;h1++)
  		{
  			printf(">>>!%d\n",h1);message[h+h1] = buffer[1+h1];
  		}printf(">>>5\n");
  		message[h+3]='\0';printf(">>>6\n");
  		label1 = gtk_label_new(message);
  		strcpy(message1,"TIME SLOT: ");
  		h = strlen(message1);
  		h2=0;
  		for(h1=0;h1<11;h1++)
  		{
  			printf(">>>##%d\n",h1);
  			if(h1==2)
  				message1[h+h1] = ':';
  			else if(h1==5)
  				message1[h+h1] = '-';
  			else if(h1==8)
  				message1[h+h1] = ':';
  			else
  			{
  				message1[h+h1] = buffer[4+h2];
  				h2++;
  			}
  		}printf(">>>7\n");
  		message1[h+h1]='\0';
  		label2 = gtk_label_new(message1);
  		gtk_fixed_put(GTK_FIXED(frame), label, 130, 180);
  		gtk_fixed_put(GTK_FIXED(frame), label1, 130, 200);
  		gtk_fixed_put(GTK_FIXED(frame), label2, 130, 220);
  		gtk_widget_show(label);
  		gtk_widget_show(label1);
  		gtk_widget_show(label2);printf(">>>8\n");
  	}
  	if(buffer[0] == 'c')
  	{	printf(">>>9\n");label = gtk_label_new("REQUEST NOT APPROVED");
  		gtk_fixed_put(GTK_FIXED(frame), label, 130, 180);
  		gtk_widget_show(label);
  	}
  }
  	 
  gtk_widget_show_all(window);
  
  g_signal_connect(window, "destroy",
      G_CALLBACK (gtk_main_quit), NULL);
      
  gtk_main();
  
  return;
}

void status_c(GtkWidget *widget, gpointer entry1)
{
	int n;
	char buffer[50];
	const char *reqid;
	reqid = gtk_entry_get_text (GTK_ENTRY(entry1));
	printf("reqid=%s\n",reqid);
	strcat(reqid,"s");
	//send reqid to server here for status || call status function here
	n = write(sockfd,reqid,strlen(reqid));
	if(n<0)
	 error("ERROR writing to socket");
	//read his reqid and dispaly,and then finally exit after 10seconds
	bzero(buffer,50);
	n = read(sockfd,buffer,49);
    	if (n < 0) 
         error("ERROR reading from socket");
        printf("n=%d***%s\n",n,buffer);
        display_status(buffer);
    	//dispaly shall be done here
    	
    	//sleep(10);
    	//exit(EXIT_SUCCESS);
}

void status_gui(GtkWidget *widget, gpointer label)
{
  GtkWidget *window;
  GtkWidget *frame;
  GtkWidget *label1;
  GtkWidget *status;
  GtkWidget *entry1;
    
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 650, 600);
  gtk_window_set_title(GTK_WINDOW(window), "STATUS CHECK");

  frame = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(window), frame);

  label1 = gtk_label_new("REQUEST ID");
  gtk_fixed_put(GTK_FIXED(frame), label1, 210, 250);
  
  entry1 = gtk_entry_new();
  gtk_fixed_put(GTK_FIXED(frame), entry1, 300, 245);
  
  status = gtk_button_new_with_label("CHECK STATUS");
  gtk_widget_set_size_request(status, 160, 30);
  gtk_fixed_put(GTK_FIXED(frame), status, 270, 280);
  
  gtk_widget_show_all(window);
  
  g_signal_connect(window, "destroy",
      G_CALLBACK (gtk_main_quit), NULL);
      
  g_signal_connect(status, "clicked", 
      G_CALLBACK(status_c), entry1);
  
  gtk_main();
  
  return;
  
  //count--;
  //sprintf(buf, "%d", count);
  //gtk_label_set_text(label, buf);
}
void portno_c(GtkWidget *widget, gpointer entry1)
{
	port_info = gtk_entry_get_text (GTK_ENTRY(entry1));
	printf("portno=%s\n",port_info);
	//send reqid to server here for status
}
void host_c(GtkWidget *widget, gpointer entry2)
{
	host_info = gtk_entry_get_text (GTK_ENTRY(entry2));
	printf("host=%s\n",host_info);
	//send reqid to server here for status
}

void connect_client(GtkWidget *widget, gpointer arbit)
{
	printf("connect_client\n");
	client();
}


void connect_gui(GtkWidget *widget, gpointer label)
{
  GtkWidget *window;
  GtkWidget *frame;
  GtkWidget *label1,*label2;
  GtkWidget *connect;
  GtkWidget *entry1,*entry2;
    
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 650, 600);
  gtk_window_set_title(GTK_WINDOW(window), "CONNECT TO SERVER");

  frame = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(window), frame);

  label1 = gtk_label_new("PORT NO");
  gtk_fixed_put(GTK_FIXED(frame), label1, 210, 250);
  
  entry1 = gtk_entry_new();
  gtk_fixed_put(GTK_FIXED(frame), entry1, 300, 245);
  
  label2 = gtk_label_new("HOSTNAME");
  gtk_fixed_put(GTK_FIXED(frame), label2, 210, 280);
  
  entry2 = gtk_entry_new();
  gtk_fixed_put(GTK_FIXED(frame), entry2, 300, 275);
  
  connect = gtk_button_new_with_label("CONNECT");
  gtk_widget_set_size_request(connect, 160, 30);
  gtk_fixed_put(GTK_FIXED(frame), connect, 270, 310);
  
  gtk_widget_show_all(window);
  
  g_signal_connect(window, "destroy",
      G_CALLBACK (gtk_main_quit), NULL);
      
  g_signal_connect(connect, "clicked", 
      G_CALLBACK(portno_c), entry1);
      
  g_signal_connect(connect, "clicked", 
      G_CALLBACK(host_c), entry2);
      
  g_signal_connect(connect, "clicked", 
      G_CALLBACK(connect_client), NULL);
  
  gtk_main();
  
  return;
  
  //count--;
  //sprintf(buf, "%d", count);
  //gtk_label_set_text(label, buf);
}

void approve_admin(GtkWidget *widget, gpointer entry1)
{
	int n;
	char buffer[256];
	const char *reqid;
	reqid = gtk_entry_get_text (GTK_ENTRY(entry1));
	strcat(reqid,"p");
	//send reqid to server here for status || call status function here
	n = write(sockfd,reqid,strlen(reqid));
	if(n<0)
	 error("ERROR writing to socket");
	//read his reqid and dispaly,and then finally exit after 10seconds
	bzero(buffer,256);
	n = read(sockfd,buffer,255);
    	if (n < 0) 
         error("ERROR reading from socket");
        display_cancel(buffer);
    	//dispaly shall be done here
    	printf("%s\n",buffer);
    	//sleep(10);
    	//exit(EXIT_SUCCESS);
}

void cancel_admin(GtkWidget *widget, gpointer entry1)
{
	int n;
	char buffer[256];
	const char *reqid;
	reqid = gtk_entry_get_text (GTK_ENTRY(entry1));
	strcat(reqid,"c");
	//send reqid to server here for status || call status function here
	n = write(sockfd,reqid,strlen(reqid));
	if(n<0)
	 error("ERROR writing to socket");
	//read his reqid and dispaly,and then finally exit after 10seconds
	bzero(buffer,256);
	n = read(sockfd,buffer,255);
    	if (n < 0) 
         error("ERROR reading from socket");
        strcpy(buffer,"REQUEST CANCELLED BY ADMIN");
        display_cancel(buffer);
    	//dispaly shall be done here
    	printf("%s\n",buffer);
    	//sleep(10);
    	//exit(EXIT_SUCCESS);
}

void admin_gui(GtkWidget *widget, gpointer label)
{
  GtkWidget *window;
  GtkWidget *frame;
  GtkWidget *label1,*label2;
  GtkWidget *approve,*cancel;
  GtkWidget *entry1,*entry2;
    
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 650, 600);
  gtk_window_set_title(GTK_WINDOW(window), "ADMINISTRATOR");

  frame = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(window), frame);

  label1 = gtk_label_new("REQUEST ID");
  gtk_fixed_put(GTK_FIXED(frame), label1, 210, 250);
  
  entry1 = gtk_entry_new();
  gtk_fixed_put(GTK_FIXED(frame), entry1, 300, 245);
  
  approve = gtk_button_new_with_label("APPROVE REQUEST");
  gtk_widget_set_size_request(approve, 160, 30);
  gtk_fixed_put(GTK_FIXED(frame), approve, 190, 280);
  
  cancel = gtk_button_new_with_label("CANCEL REQUEST");
  gtk_widget_set_size_request(cancel, 160, 30);
  gtk_fixed_put(GTK_FIXED(frame), cancel, 350, 280);
  
  gtk_widget_show_all(window);
  
  g_signal_connect(window, "destroy",
      G_CALLBACK (gtk_main_quit), NULL);
      
  g_signal_connect(approve, "clicked", 
      G_CALLBACK(approve_admin), entry1);
      
  g_signal_connect(cancel, "clicked", 
      G_CALLBACK(cancel_admin), entry1);
      
    
  gtk_main();
  
  return;
  
  //count--;
  //sprintf(buf, "%d", count);
  //gtk_label_set_text(label, buf);
}

void gui(int argc, char **argv)
{
  refresh_data(data_user);
  printf("in main data_user = %s\n",data_user);
  
  GtkWidget *label;
  GtkWidget *window;
  GtkWidget *frame;
  GtkWidget *book;
  GtkWidget *cancel;
  GtkWidget *status;
  GtkWidget *connect;  
  GtkWidget *quit;
  GtkWidget *admin;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 650, 600);
  gtk_window_set_title(GTK_WINDOW(window), "main");

  frame = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(window), frame);

  connect = gtk_button_new_with_label("CONNECT TO SERVER");
  gtk_widget_set_size_request(connect, 400, 50);
  gtk_fixed_put(GTK_FIXED(frame), connect, 125, 150);
  
  book = gtk_button_new_with_label("BOOK YOUR ROOM");
  gtk_widget_set_size_request(book, 400, 50);
  gtk_fixed_put(GTK_FIXED(frame), book, 125, 200);

  cancel = gtk_button_new_with_label("CANCEL REQUEST");
  gtk_widget_set_size_request(cancel, 400, 50);
  gtk_fixed_put(GTK_FIXED(frame), cancel, 125, 250);
  
  status = gtk_button_new_with_label("CHECK BOOKING STATUS");
  gtk_widget_set_size_request(status, 400, 50);
  gtk_fixed_put(GTK_FIXED(frame), status, 125, 300);
  
  admin = gtk_button_new_with_label("LOGIN AS ADMIN");
  gtk_widget_set_size_request(admin, 400, 50);
  gtk_fixed_put(GTK_FIXED(frame), admin, 125, 350);
  
  quit = gtk_button_new_with_label("QUIT");
  gtk_widget_set_size_request(quit, 400, 50);
  gtk_fixed_put(GTK_FIXED(frame), quit, 125, 400);

  label = gtk_label_new("BOOKING SYSTEM");
  gtk_fixed_put(GTK_FIXED(frame), label, 267, 80); 

  gtk_widget_show_all(window);

  g_signal_connect(window, "destroy",
      G_CALLBACK (gtk_main_quit), NULL);

  g_signal_connect(connect, "clicked", 
      G_CALLBACK(connect_gui), NULL);
      
  g_signal_connect(book, "clicked", 
      G_CALLBACK(book_gui), NULL);

  g_signal_connect(cancel, "clicked", 
      G_CALLBACK(cancel_gui), label);
  
  g_signal_connect(status, "clicked", 
      G_CALLBACK(status_gui), label);
      
  g_signal_connect(admin, "clicked", 
      G_CALLBACK(admin_gui), label);
      
  g_signal_connect(G_OBJECT(quit), "clicked",
      G_CALLBACK(gtk_main_quit), NULL);

  gtk_main();

  return;
}

int main(int argc, char** argv) {

    gui(argc,argv);
  
  return 0;
}
