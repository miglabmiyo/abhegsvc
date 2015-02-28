
###############################################################################
## 编译器
COMPILER = g++
COMPILERC = gcc

## 编译选项
## for debug -DROOM_DEBUG_MCACHE
CPP_FLAG = -g -Wall -w -fPIC -c -D_LINUX -DDEBUG -D_DEBUG -D_REENTRANT -D_GNU_SOURCE -D__DEBUG_CORE__ -DFCGI_STD  #-DCHECK_HEADER-DTEST
RCPP_FLAG = -g -Wall -w -fPIC -c -D_LINUX -DDEBUG -D_DEBUG -D_REENTRANT -D_GNU_SOURCE -DFCGI_STD #-DTEST
## for release
##CPP_FLAG = -O3 -Wall -s -w -fPIC -c -D_LINUX -DNDEBUG -D_REENTRANT -D_GNU_SOURCE -DFCGI_STD

## 链接选项
## for debug
LINK_FLAGS = -g  -fPIC
## for release
## LINK_FLAGS = -s -O3 -shared -fPIC

LIB_DIR = ./../../library
BASE_DIR = ./../pub
## 头文件
INCLUDE_PATHS = -I$(LIB_DIR)/public/ -I /usr/local/libmemcached-1.0.7/include\
		-I/usr/local/lib -I$(LIB_DIR)/third_party/hiredis -I$(BASE_DIR)/\
		-I$(LIB_DIR)/third_party/breakpad/src

## 库
LINK_PATHS =  -L/usr/local/libmemcached-1.0.7/lib/ -L/usr/lib64/mysql
LINK_LIBRARYS = -lmemcached -lmemcachedutil -lrt -lpthread  -liconv -lfcgi++ -lmysqlclient -lexpat -lcurl\
					./../lib/libbreakpad_client.a ./../lib/libhiredis.a $(LINK_CORE_PATH)

# 编译
COMPILE = $(COMPILER) $(CPP_FLAG) $(INCLUDE_PATHS) -o $@
RCOMPILE = $(COMPILER) $(RCPP_FLAG) $(INCLUDE_PATHS) -o $@

# 链接
LINK = $(COMPILER) $(LINK_FLAGS) $(LINK_PATHS) $? -o $(OUTPUT_FILE) $(LINK_LIBRARYS)
LINKALL = $(COMPILER) $(LINK_FLAGS) $(LINK_PATHS) $?  $(LINK_LIBRARYS)











POBJ =  mig_log.o core_interface.o
OUTPUT_FILE = /var/www/cgi-bin/abheg
#############################################################################################################################
all: clean proc delete-temp-file

proc: otherproc userproc findproc bookproc musicproc robotproc storeproc


######################musicproc###############################################
MUSICNAME = music_
MUSICPROC_PATH = /music
MUSIC_OBJECT_PATH = ./obj$(MUSICPROC_PATH)
OTJERPROC_VERSION = /v1
musicproc:$(MUSICPROC_PATH)/getcltsongs.fcgi $(MUSICPROC_PATH)/getdimension.fcgi

$(MUSICPROC_PATH)/getcltsongs.fcgi: $(MUSIC_OBJECT_PATH)/$(MUSICNAME)getcltsongs.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(MUSICPROC_PATH)$(OTJERPROC_VERSION)/getcltsongs.fcgi

$(MUSICPROC_PATH)/getdimension.fcgi: $(MUSIC_OBJECT_PATH)/$(MUSICNAME)getdimension.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(MUSICPROC_PATH)$(OTJERPROC_VERSION)/getdimension.fcgi

### 编译

$(MUSIC_OBJECT_PATH)/$(MUSICNAME)getcltsongs.o:
	$(COMPILE) .$(MUSICPROC_PATH)$(OTJERPROC_VERSION)/getcltsongs/getcltsongs.cc

$(MUSIC_OBJECT_PATH)/$(MUSICNAME)getdimension.o:
	$(COMPILE) .$(MUSICPROC_PATH)$(OTJERPROC_VERSION)/getdimension/getdimension.cc


	
######################otherproc###############################################
OTHERPROC_PATH = /other
OTJERPROC_VERSION = /1
otherproc:checkapi.fcgi

checkapi.fcgi: checkapi.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(OTHERPROC_PATH)$(OTJERPROC_VERSION)/checkapi.fcgi
	
### 编译

checkapi.o:
	$(COMPILE) .$(OTHERPROC_PATH)$(OTJERPROC_VERSION)/checkapi/checkapi.cc
	
######################robotproc###############################################
ROBOTNAME = robot_
ROBOTPROC_PATH = /robot
ROBOT_OBJECT_PATH = ./obj$(ROBOTPROC_PATH)
OTJERPROC_VERSION = /1
robotproc:$(ROBOTPROC_PATH)/spiderphone.fcgi

$(ROBOTPROC_PATH)/spiderphone.fcgi: $(ROBOT_OBJECT_PATH)/$(ROBOTNAME)spiderphone.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(ROBOTPROC_PATH)$(OTJERPROC_VERSION)/spiderphone.fcgi
	
### 编译

$(ROBOT_OBJECT_PATH)/$(ROBOTNAME)spiderphone.o:
	$(COMPILE) .$(ROBOTPROC_PATH)$(OTJERPROC_VERSION)/spiderphone/spiderphone.cc
	
######################bookproc###############################################
BOOKNAME = book_
BOOKPROC_PATH = /book
BOOK_OBJECT_PATH = ./obj$(BOOKPROC_PATH)
OTJERPROC_VERSION = /1
bookproc:$(BOOKPROC_PATH)/booklist.fcgi $(BOOKPROC_PATH)/searchtype.fcgi $(BOOKPROC_PATH)/wanted.fcgi $(BOOKPROC_PATH)/chapterlist.fcgi\
	$(BOOKPROC_PATH)/booksummary.fcgi $(BOOKPROC_PATH)/topics.fcgi

$(BOOKPROC_PATH)/topics.fcgi: $(BOOK_OBJECT_PATH)/$(BOOKNAME)topics.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(BOOKPROC_PATH)$(OTJERPROC_VERSION)/topics.fcgi
	
$(BOOKPROC_PATH)/searchtype.fcgi: $(BOOK_OBJECT_PATH)/$(BOOKNAME)searchtype.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(BOOKPROC_PATH)$(OTJERPROC_VERSION)/searchtype.fcgi
	
$(BOOKPROC_PATH)/wanted.fcgi: $(BOOK_OBJECT_PATH)/$(BOOKNAME)wanted.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(BOOKPROC_PATH)$(OTJERPROC_VERSION)/wanted.fcgi
	
$(BOOKPROC_PATH)/booklist.fcgi: $(BOOK_OBJECT_PATH)/$(BOOKNAME)booklist.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(BOOKPROC_PATH)$(OTJERPROC_VERSION)/booklist.fcgi
	
$(BOOKPROC_PATH)/chapterlist.fcgi: $(BOOK_OBJECT_PATH)/$(BOOKNAME)chapterlist.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(BOOKPROC_PATH)$(OTJERPROC_VERSION)/chapterlist.fcgi
	
$(BOOKPROC_PATH)/booksummary.fcgi: $(BOOK_OBJECT_PATH)/$(BOOKNAME)booksummary.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(BOOKPROC_PATH)$(OTJERPROC_VERSION)/booksummary.fcgi
### 编译

$(BOOK_OBJECT_PATH)/$(BOOKNAME)topics.o:
	$(COMPILE) .$(BOOKPROC_PATH)$(OTJERPROC_VERSION)/topics/topics.cc
	
$(BOOK_OBJECT_PATH)/$(BOOKNAME)searchtype.o:
	$(COMPILE) .$(BOOKPROC_PATH)$(OTJERPROC_VERSION)/searchtype/searchtype.cc
	
$(BOOK_OBJECT_PATH)/$(BOOKNAME)wanted.o:
	$(COMPILE) .$(BOOKPROC_PATH)$(OTJERPROC_VERSION)/wanted/wanted.cc
	
$(BOOK_OBJECT_PATH)/$(BOOKNAME)booklist.o:
	$(COMPILE) .$(BOOKPROC_PATH)$(OTJERPROC_VERSION)/booklist/booklist.cc
	
$(BOOK_OBJECT_PATH)/$(BOOKNAME)chapterlist.o:
	$(COMPILE) .$(BOOKPROC_PATH)$(OTJERPROC_VERSION)/chapterlist/chapterlist.cc
	
$(BOOK_OBJECT_PATH)/$(BOOKNAME)booksummary.o:
	$(COMPILE) .$(BOOKPROC_PATH)$(OTJERPROC_VERSION)/summary/summary.cc
	
######################storeproc###############################################
STORENAME = store_
STOREPROC_PATH = /store
STORE_OBJECT_PATH = ./obj$(STOREPROC_PATH)
OTJERPROC_VERSION = /1
storeproc:$(STOREPROC_PATH)/summary.fcgi $(STOREPROC_PATH)/wanted.fcgi $(STOREPROC_PATH)/like.fcgi \
	$(STOREPROC_PATH)/topics.fcgi $(STOREPROC_PATH)/searchkey.fcgi $(STOREPROC_PATH)/searchtype.fcgi

$(STOREPROC_PATH)/wanted.fcgi: $(STORE_OBJECT_PATH)/$(STORENAME)wanted.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(STOREPROC_PATH)$(OTJERPROC_VERSION)/wanted.fcgi
	
$(STOREPROC_PATH)/summary.fcgi: $(STORE_OBJECT_PATH)/$(STORENAME)summary.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(STOREPROC_PATH)$(OTJERPROC_VERSION)/summary.fcgi
	
$(STOREPROC_PATH)/like.fcgi: $(STORE_OBJECT_PATH)/$(STORENAME)like.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(STOREPROC_PATH)$(OTJERPROC_VERSION)/like.fcgi
	
$(STOREPROC_PATH)/topics.fcgi: $(STORE_OBJECT_PATH)/$(STORENAME)topics.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(STOREPROC_PATH)$(OTJERPROC_VERSION)/topics.fcgi
	
$(STOREPROC_PATH)/searchkey.fcgi: $(STORE_OBJECT_PATH)/$(STORENAME)searchkey.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(STOREPROC_PATH)$(OTJERPROC_VERSION)/searchkey.fcgi

$(STOREPROC_PATH)/searchtype.fcgi: $(STORE_OBJECT_PATH)/$(STORENAME)searchtype.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(STOREPROC_PATH)$(OTJERPROC_VERSION)/searchtype.fcgi


	
### 编译

$(STORE_OBJECT_PATH)/$(STORENAME)summary.o:
	$(COMPILE) .$(STOREPROC_PATH)$(OTJERPROC_VERSION)/summary/summary.cc
	
$(STORE_OBJECT_PATH)/$(STORENAME)wanted.o:
	$(COMPILE) .$(STOREPROC_PATH)$(OTJERPROC_VERSION)/wanted/wanted.cc
	
$(STORE_OBJECT_PATH)/$(STORENAME)like.o:
	$(COMPILE) .$(STOREPROC_PATH)$(OTJERPROC_VERSION)/like/like.cc
	
$(STORE_OBJECT_PATH)/$(STORENAME)topics.o:
	$(COMPILE) .$(STOREPROC_PATH)$(OTJERPROC_VERSION)/topics/topics.cc
	
$(STORE_OBJECT_PATH)/$(STORENAME)searchkey.o:
	$(COMPILE) .$(STOREPROC_PATH)$(OTJERPROC_VERSION)/searchkey/searchkey.cc
	
$(STORE_OBJECT_PATH)/$(STORENAME)searchtype.o:
	$(COMPILE) .$(STOREPROC_PATH)$(OTJERPROC_VERSION)/appsearchtype/appsearchtype.cc
	

	
######################userproc###############################################
USERNAME = user_
USERPROC_PATH = /user
USER_OBJECT_PATH = ./obj$(USERPROC_PATH)
OTJERPROC_VERSION = /1
userproc:$(USERPROC_PATH)/quicklogin.fcgi $(USERPROC_PATH)/bdbindpush.fcgi $(USERPROC_PATH)/thirdlogin.fcgi

$(USERPROC_PATH)/quicklogin.fcgi: $(USER_OBJECT_PATH)/$(USERNAME)quicklogin.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(USERPROC_PATH)$(OTJERPROC_VERSION)/quicklogin.fcgi

$(USERPROC_PATH)/thirdlogin.fcgi: $(USER_OBJECT_PATH)/$(USERNAME)thirdlogin.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(USERPROC_PATH)$(OTJERPROC_VERSION)/thirdlogin.fcgi
	
$(USERPROC_PATH)/bdbindpush.fcgi: $(USER_OBJECT_PATH)/$(USERNAME)bindpush.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(USERPROC_PATH)$(OTJERPROC_VERSION)/bdbindpush.fcgi
	
### 编译

$(USER_OBJECT_PATH)/$(USERNAME)quicklogin.o:
	$(COMPILE) .$(USERPROC_PATH)$(OTJERPROC_VERSION)/quicklogin/quicklogin.cc
	
$(USER_OBJECT_PATH)/$(USERNAME)bindpush.o:
	$(COMPILE) .$(USERPROC_PATH)$(OTJERPROC_VERSION)/bindpush/bindpush.cc

$(USER_OBJECT_PATH)/$(USERNAME)thirdlogin.o:
	$(COMPILE) .$(USERPROC_PATH)$(OTJERPROC_VERSION)/thirdlogin/thirdlogin.cc
	
	
######################findproc###############################################
FINDNAME = find_
FINDPROC_PATH = /find
FIND_OBJECT_PATH = ./obj$(FINDPROC_PATH)
OTJERPROC_VERSION = /1
findproc:$(FINDPROC_PATH)/appstore.fcgi $(FINDPROC_PATH)/bookstore.fcgi $(FINDPROC_PATH)/gamestore.fcgi $(FINDPROC_PATH)/main.fcgi\
	$(FINDPROC_PATH)/gamerank.fcgi

$(FINDPROC_PATH)/appstore.fcgi: $(FIND_OBJECT_PATH)/$(FINDNAME)appstore.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(FINDPROC_PATH)$(OTJERPROC_VERSION)/appstore.fcgi
	
$(FINDPROC_PATH)/bookstore.fcgi: $(FIND_OBJECT_PATH)/$(FINDNAME)bookstore.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(FINDPROC_PATH)$(OTJERPROC_VERSION)/bookstore.fcgi
	
$(FINDPROC_PATH)/gamestore.fcgi: $(FIND_OBJECT_PATH)/$(FINDNAME)gamestore.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(FINDPROC_PATH)$(OTJERPROC_VERSION)/gamestore.fcgi
	
$(FINDPROC_PATH)/main.fcgi: $(FIND_OBJECT_PATH)/$(FINDNAME)main.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(FINDPROC_PATH)$(OTJERPROC_VERSION)/main.fcgi
	
$(FINDPROC_PATH)/gamerank.fcgi: $(FIND_OBJECT_PATH)/$(FINDNAME)gamerank.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(FINDPROC_PATH)$(OTJERPROC_VERSION)/gamerank.fcgi
### 编译

$(FIND_OBJECT_PATH)/$(FINDNAME)appstore.o:
	$(COMPILE) .$(FINDPROC_PATH)$(OTJERPROC_VERSION)/appstore/appstore.cc

$(FIND_OBJECT_PATH)/$(FINDNAME)bookstore.o:
	$(COMPILE) .$(FINDPROC_PATH)$(OTJERPROC_VERSION)/bookstore/bookstore.cc
	
$(FIND_OBJECT_PATH)/$(FINDNAME)gamestore.o:
	$(COMPILE) .$(FINDPROC_PATH)$(OTJERPROC_VERSION)/gamestore/gamestore.cc
	
$(FIND_OBJECT_PATH)/$(FINDNAME)main.o:
	$(COMPILE) .$(FINDPROC_PATH)$(OTJERPROC_VERSION)/main/main.cc
	
$(FIND_OBJECT_PATH)/$(FINDNAME)gamerank.o:
	$(COMPILE) .$(FINDPROC_PATH)$(OTJERPROC_VERSION)/gamerank/gamerank.cc

clean:
	-rm -f *.o
	-rm -f $(OUTPUT_FILE)./*.fcgi

delete-temp-file:
	-rm -f *.o

############public###############################
mig_log.o:
	$(COMPILE) $(LIB_DIR)/public/log/mig_log.cc

core_interface.o:
	$(COMPILE) $(LIB_DIR)/public/comm/core_interface.cc
