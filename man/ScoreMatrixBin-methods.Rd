% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/scoreMatrixBin.R
\docType{methods}
\name{ScoreMatrixBin}
\alias{ScoreMatrixBin}
\alias{ScoreMatrixBin,RleList,GRanges-method}
\alias{ScoreMatrixBin,GRanges,GRanges-method}
\alias{ScoreMatrixBin,character,GRanges-method}
\alias{ScoreMatrixBin,RleList,GRangesList-method}
\alias{ScoreMatrixBin,GRanges,GRangesList-method}
\alias{ScoreMatrixBin,character,GRangesList-method}
\title{Get bin score for bins on each window}
\usage{
ScoreMatrixBin(target, windows, bin.num = 10, bin.op = "mean",
  strand.aware = FALSE, weight.col = NULL, is.noCovNA = FALSE,
  type = "auto", rpm = FALSE, unique = FALSE, extend = 0,
  param = NULL, bam.paired.end = FALSE, library.size = NULL)

\\S4method{ScoreMatrixBin}{RleList,GRanges}(target, windows, bin.num, bin.op,
                                                   strand.aware)

\\S4method{ScoreMatrixBin}{GRanges,GRanges}(target,windows,
                                                   bin.num,bin.op,
                                                   strand.aware,weight.col,
                                                   is.noCovNA)

\\S4method{ScoreMatrixBin}{character,GRanges}(target, windows, bin.num=10,
                                                     bin.op='mean',strand.aware, 
                                                     weight.col=NULL,
                                                     is.noCovNA=FALSE, type='auto',
                                                     rpm, unique, extend, param,
                                                     bam.paired.end=FALSE, 
                                                     library.size=NULL)

\\S4method{ScoreMatrixBin}{RleList,GRangesList}(target,windows,
                                                        bin.num, bin.op,
                                                        strand.aware)

\\S4method{ScoreMatrixBin}{GRanges,GRangesList}(target,windows,
                                                   bin.num,bin.op,
                                                   strand.aware,weight.col,
                                                   is.noCovNA)

\\S4method{ScoreMatrixBin}{character,GRangesList}(target, windows, bin.num=10,
                                                     bin.op='mean',strand.aware, 
                                                     weight.col=NULL,
                                                     is.noCovNA=FALSE, type='auto',
                                                     rpm, unique, extend, param,
                                                     bam.paired.end=FALSE, 
                                                     library.size=NULL)
}
\arguments{
\item{target}{\code{RleList}, \code{GRanges}, a BAM file or a bigWig file 
object to be overlapped with ranges in \code{windows}}

\item{windows}{\code{GRanges} or \code{GRangesList} object that contains
the windows of interest. It could be promoters, CpG islands, 
exons, introns as GRanges object or GrangesList object representing
exons of each transcript. Exons must be ordered by ascending rank
by their position in transcript. The sizes of windows 
does NOT have to be equal.}

\item{bin.num}{single \code{integer} value denoting how many bins there 
should be for each window}

\item{bin.op}{bin operation that is either one of the following strings: 
"max","min","mean". The operation is applied on the 
values in the bin. Defaults to "mean"}

\item{strand.aware}{If TRUE (default: FALSE), the strands of the windows will 
be taken into account in the resulting \code{scoreMatrix}. 
If the strand of a window is -, the values of the bins 
for that window will be reversed}

\item{weight.col}{if the object is \code{GRanges} object a numeric column
in meta data part can be used as weights. This is particularly
useful when genomic regions have scores other than their
coverage values, such as percent methylation, conservation
scores, GC content, etc.}

\item{is.noCovNA}{(Default:FALSE)
if TRUE,and if 'target' is a GRanges object with 'weight.col'
 provided, the bases that are uncovered will be preserved as
 NA in the returned object. This useful for situations where
 you can not have coverage all over the genome, such as CpG
  methylation values.}

\item{type}{(Default:"auto")
if target is a character vector of file paths, then type designates 
the type of the corresponding files (bam or bigWig)}

\item{rpm}{boolean telling whether to normalize the coverage to per milion reads. 
FALSE by default. See \code{library.size}.}

\item{unique}{boolean which tells the function to remove duplicated reads 
based on chr, start, end and strand}

\item{extend}{numeric which tells the function to extend the reads to width=extend}

\item{param}{ScanBamParam object}

\item{bam.paired.end}{boolean indicating whether given BAM file contains paired-end 
reads (default:FALSE). Paired-reads will be treated as 
fragments.}

\item{library.size}{numeric indicating total number of mapped reads in a BAM file
(\code{rpm} has to be set to TRUE).
If is not given (default: NULL) then library size 
is calculated using the Rsamtools idxstatsBam function:
sum(idxstatsBam(target)$mapped).}
}
\value{
returns a \code{scoreMatrix} object
}
\description{
The function first bins each window to equal number of bins, and calculates
the a summary matrix for scores of each bin (currently, mean, max and min supported)
A scoreMatrix object can be used to draw average profiles or heatmap of read coverage
or wig track-like data. \code{windows} can be a predefined region such as CpG islands,
gene bodies, transcripts or CDS (coding sequences) that are not necessarily equi-width. 
Each window will be chopped to equal number of bins based on \code{bin.num} option.
}
\examples{
data(cage)
data(cpgi)
data(promoters)
myMat=ScoreMatrixBin(target=cage,
                      windows=cpgi,bin.num=10,bin.op="mean",weight.col="tpm")
\donttest{
plot(colMeans(myMat,na.rm=TRUE),type="l")
}
  
myMat2=ScoreMatrixBin(target=cage,
                       windows=promoters,bin.num=10,bin.op="mean",
                       weight.col="tpm",strand.aware=TRUE)
\donttest{
plot(colMeans(myMat2,na.rm=TRUE),type="l")
}

# Compute transcript coverage of a set of exons.
library(GenomicRanges)
bed.file = system.file("extdata/chr21.refseq.hg19.bed", 
                       package = "genomation")
gene.parts = readTranscriptFeatures(bed.file)
transcripts = split(gene.parts$exons, gene.parts$exons$name)
transcripts = transcripts[]
myMat3 = ScoreMatrixBin(target=cage, windows=transcripts[1:250], 
                    bin.num=10)
myMat3                     
}
\seealso{
\code{\link{ScoreMatrix}}
}
