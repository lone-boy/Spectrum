//
// Created by jcc on 22-11-25.
//

#ifndef SPECTRUM_MATHCOMMON_H
#define SPECTRUM_MATHCOMMON_H
#include "QVector"

/**
 * moving average algorithm
 * */
void fft_data_avarage(QVector<double>& fft_data,int avarage_point,int all_sample_size){
    if(avarage_point == 1){
        return;
    }

    for(int i = 0;i < fft_data.size();i++){
        int index = i - avarage_point / 2 ;
        int index_end = index + avarage_point;
        double temp = 0.f;
        int cnt = 0;
        for(;index < index_end;index++){
            if(index >= 0 && index < all_sample_size){
                cnt++;
                temp += fft_data[index];
            }
        }
        fft_data[i] = temp / cnt;
    }
}


#endif //SPECTRUM_MATHCOMMON_H
