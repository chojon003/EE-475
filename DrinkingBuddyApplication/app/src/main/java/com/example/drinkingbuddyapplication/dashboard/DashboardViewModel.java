package com.example.drinkingbuddyapplication.dashboard;

import androidx.lifecycle.LiveData;
import androidx.lifecycle.MutableLiveData;
import androidx.lifecycle.ViewModel;

public class DashboardViewModel extends ViewModel {

    private MutableLiveData<String> mText;

    public DashboardViewModel() {
        mText = new MutableLiveData<>();
        mText.setValue("Daily Water Consumption Over Time");
    }

    public LiveData<String> getText() {
        return mText;
    }
}