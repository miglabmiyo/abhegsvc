
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

proc: otherproc userproc findproc storeproc bookproc

	
######################otherproc###############################################
OTHERPROC_PATH = /other
OTJERPROC_VERSION = /1
otherproc:checkapi.fcgi

checkapi.fcgi: checkapi.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(OTHERPROC_PATH)$(OTJERPROC_VERSION)/checkapi.fcgi
	
### 编译

checkapi.o:
	$(COMPILE) .$(OTHERPROC_PATH)$(OTJERPROC_VERSION)/checkapi/checkapi.cc
	
######################bookproc###############################################
BOOKPROC_PATH = /book
OTJERPROC_VERSION = /1
bookproc:topics.fcgi searchtype.fcgi wanted.fcgi booklist.fcgi chapterlist.fcgi

topics.fcgi: topics.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(BOOKPROC_PATH)$(OTJERPROC_VERSION)/topics.fcgi
	
searchtype.fcgi: searchtype.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(BOOKPROC_PATH)$(OTJERPROC_VERSION)/searchtype.fcgi
	
wanted.fcgi: wanted.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(BOOKPROC_PATH)$(OTJERPROC_VERSION)/wanted.fcgi
	
booklist.fcgi: booklist.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(BOOKPROC_PATH)$(OTJERPROC_VERSION)/booklist.fcgi
	
chapterlist.fcgi: chapterlist.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(BOOKPROC_PATH)$(OTJERPROC_VERSION)/chapterlist.fcgi
### 编译

topics.o:
	$(COMPILE) .$(BOOKPROC_PATH)$(OTJERPROC_VERSION)/topics/topics.cc
	
searchtype.o:
	$(COMPILE) .$(BOOKPROC_PATH)$(OTJERPROC_VERSION)/searchtype/searchtype.cc
	
wanted.o:
	$(COMPILE) .$(BOOKPROC_PATH)$(OTJERPROC_VERSION)/wanted/wanted.cc
	
booklist.o:
	$(COMPILE) .$(BOOKPROC_PATH)$(OTJERPROC_VERSION)/booklist/booklist.cc
	
chapterlist.o:
	$(COMPILE) .$(BOOKPROC_PATH)$(OTJERPROC_VERSION)/chapterlist/chapterlist.cc
	
######################storeproc###############################################
STOREPROC_PATH = /store
OTJERPROC_VERSION = /1
storeproc:summary.fcgi wanted.fcgi like.fcgi

wanted.fcgi: wanted.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(STOREPROC_PATH)$(OTJERPROC_VERSION)/wanted.fcgi
	
summary.fcgi: summary.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(STOREPROC_PATH)$(OTJERPROC_VERSION)/summary.fcgi
	
like.fcgi: like.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(STOREPROC_PATH)$(OTJERPROC_VERSION)/like.fcgi
	
### 编译

summary.o:
	$(COMPILE) .$(STOREPROC_PATH)$(OTJERPROC_VERSION)/summary/summary.cc
	
wanted.o:
	$(COMPILE) .$(STOREPROC_PATH)$(OTJERPROC_VERSION)/wanted/wanted.cc
	
like.o:
	$(COMPILE) .$(STOREPROC_PATH)$(OTJERPROC_VERSION)/like/like.cc

	
######################userproc###############################################
USERPROC_PATH = /user
OTJERPROC_VERSION = /1
userproc:quicklogin.fcgi bdbindpush.fcgi thirdlogin.fcgi

quicklogin.fcgi: quicklogin.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(USERPROC_PATH)$(OTJERPROC_VERSION)/quicklogin.fcgi

thirdlogin.fcgi: thirdlogin.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(USERPROC_PATH)$(OTJERPROC_VERSION)/thirdlogin.fcgi
	
bdbindpush.fcgi: bindpush.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(USERPROC_PATH)$(OTJERPROC_VERSION)/bdbindpush.fcgi
	
### 编译

quicklogin.o:
	$(COMPILE) .$(USERPROC_PATH)$(OTJERPROC_VERSION)/quicklogin/quicklogin.cc
	
bindpush.o:
	$(COMPILE) .$(USERPROC_PATH)$(OTJERPROC_VERSION)/bindpush/bindpush.cc

thirdlogin.o:
	$(COMPILE) .$(USERPROC_PATH)$(OTJERPROC_VERSION)/thirdlogin/thirdlogin.cc
	
	
######################findproc###############################################
FINDPROC_PATH = /find
OTJERPROC_VERSION = /1
findproc:appstore.fcgi bookstore.fcgi gamestore.fcgi main.fcgi

appstore.fcgi: appstore.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(FINDPROC_PATH)$(OTJERPROC_VERSION)/appstore.fcgi
	
bookstore.fcgi: bookstore.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(FINDPROC_PATH)$(OTJERPROC_VERSION)/bookstore.fcgi
	
gamestore.fcgi: gamestore.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(FINDPROC_PATH)$(OTJERPROC_VERSION)/gamestore.fcgi
	
main.fcgi: main.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(FINDPROC_PATH)$(OTJERPROC_VERSION)/main.fcgi
### 编译

appstore.o:
	$(COMPILE) .$(FINDPROC_PATH)$(OTJERPROC_VERSION)/appstore/appstore.cc

bookstore.o:
	$(COMPILE) .$(FINDPROC_PATH)$(OTJERPROC_VERSION)/bookstore/bookstore.cc
	
gamestore.o:
	$(COMPILE) .$(FINDPROC_PATH)$(OTJERPROC_VERSION)/gamestore/gamestore.cc
	
main.o:
	$(COMPILE) .$(FINDPROC_PATH)$(OTJERPROC_VERSION)/main/main.cc

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
