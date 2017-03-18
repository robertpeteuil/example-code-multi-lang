#The purpose of this code is to extract the top grossing movies of 2014 from the site BoxOfficeMojo.com

boxofficeStart <- function(){
  #Load libraries and create empty data.frame
  library(rvest)
  library(plyr)

  boxofficeAll <<- data.frame()
}

boxofficeScrape <- function(year){

  url <- html(paste("http://www.boxofficemojo.com/yearly/chart/?yr=",year,"&p=.htm/", sep=""))

  #Look for all html elements that contain relevant box office data for given year
  k<- url %>%
    html_nodes("td") %>%
    html_text()

  if (year >= 2002){
    #Capture only <td> elements that contain data of interest
    k<- k[c(13:14, 17:920)]

    #Add missing value excluded from previous line of code
    k<- append(k, "Studio", after = 2)

    #Split two values in order to properly align headers with columns
    x<- unlist(strsplit(k[4], "/"))
    k <- k[-4]
    k<- append(k, x, after = 3)

    x<- unlist(strsplit(k[6], "/"))
    k <- k[-6]
    k<- append(k, x, after = 5)

    #Create data frame and assign first row values as column names
    k <- as.data.frame(matrix(k, nrow = 101, ncol = 9, byrow = TRUE))
    colnames(k)<- as.character(unlist(k[1,]))
    k <- k[-1,]

    #Rename the two identical column names
    colnames(k) <- c("Rank", "Title", "Studio", "Total Gross", "Total Theaters", "Opening", "Opening Theatres", "Open Date", "Close Date")

    #Re-class the values for analysis
    k[,4:7]<- sapply(k[,4:7], function(k) gsub(",","",k))
    k[,4:7]<- as.numeric(sapply(k[,4:7], function(k) gsub("\\$","",k)))

    #Convert date columns. Columns default to current year and need to be retrofitted with correct release year
    k[,8] <- as.POSIXct(as.Date(k[,8],"%m/%d"))
    k[,9] <- as.POSIXct(as.Date(k[,9],"%m/%d"))

    x <- as.POSIXlt(k[,8])
    y <- as.POSIXlt(k[,9])
    x$year <- (year-1900)

    #for(j in 1:length(y)){
      #if((y$yday[j] > x$yday[j]) & (!is.na(y$yday[j]))){

        #y$year[j] <- y$year[j] - 1}
    #}

    k[,8] <- x$year
    k[,8] <- as.Date(as.POSIXct(x))

    k[,9] <- y$year
    k[,9] <- as.Date(as.POSIXct(y))

    boxofficeAll <<- rbind.fill(boxofficeAll, k)
    rm(k)


  }
  else {
    #Capture only <td> elements that contain data of interest
    k<- k[c(13:14, 17:819)]

    #Add missing value excluded from previous line of code
    k<- append(k, "Studio", after = 2)

    #Split two values in order to properly align headers with columns
    x<- unlist(strsplit(k[4], "/"))
    k <- k[-4]
    k<- append(k, x, after = 3)

    x<- unlist(strsplit(k[6], "/"))
    k <- k[-6]
    k<- append(k, x, after = 5)

    #Create data frame and assign first row values as column names
    k <- as.data.frame(matrix(k, nrow = 101, ncol = 8, byrow = TRUE))
    colnames(k)<- as.character(unlist(k[1,]))
    k <- k[-1,]

    #Rename the two identical column names
    colnames(k) <- c("Rank", "Title", "Studio", "Total Gross", "Total Theaters", "Opening", "Opening Theatres", "Open Date")

    #Re-class the values for analysis
    k[,4:7]<- sapply(k[,4:7], function(k) gsub(",","",k))
    k[,4:7]<- as.numeric(sapply(k[,4:7], function(k) gsub("\\$","",k)))

    #Convert date columns. Columns default to current year and need to be retrofitted with correct release year
    k[,8] <- as.POSIXct(as.Date(k[,8],"%m/%d"))


    x <- as.POSIXlt(k[,8])

    x$year <- (year-1900)


    k[,8] <- x$year
    k[,8] <- as.Date(as.POSIXct(x))


    boxofficeAll <<- rbind.fill(boxofficeAll, k)
    rm(k)

  }
}


boxofficeSTATS <- function (){
  summary(boxofficeAll)
  hist(na.omit(boxofficeAll[,4]))
  myts <- ts(boxofficeAll, frequency = 12)
  plot(myts)
}
#NEED TO FIX CLOSE YEAR AND TIME SERIES
