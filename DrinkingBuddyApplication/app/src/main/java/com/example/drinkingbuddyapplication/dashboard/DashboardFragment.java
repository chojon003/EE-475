package com.example.drinkingbuddyapplication.dashboard;

import android.content.Context;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.Observer;
import androidx.lifecycle.ViewModelProvider;

import com.example.drinkingbuddyapplication.R;
import com.example.drinkingbuddyapplication.databinding.FragmentDashboardBinding;
import com.jjoe64.graphview.GraphView;
import com.jjoe64.graphview.GridLabelRenderer;
import com.jjoe64.graphview.series.DataPoint;
import com.jjoe64.graphview.series.LineGraphSeries;

public class DashboardFragment extends Fragment {

    private DashboardViewModel dashboardViewModel;
    private FragmentDashboardBinding binding;

    public View onCreateView(@NonNull LayoutInflater inflater,
                             ViewGroup container, Bundle savedInstanceState) {
        dashboardViewModel =
                new ViewModelProvider(this).get(DashboardViewModel.class);

        binding = FragmentDashboardBinding.inflate(inflater, container, false);
        View root = binding.getRoot();

        final TextView textView = binding.textDashboard;
        dashboardViewModel.getText().observe(getViewLifecycleOwner(), new Observer<String>() {
            @Override
            public void onChanged(@Nullable String s) {
                textView.setText(s);
            }
        });
        // instantiate local variables
        SharedPreferences pref = getActivity().getPreferences(Context.MODE_PRIVATE);

        // read data
        int SevenDaysAgo = pref.getInt("Seven", 3000);
        int SixDaysAgo = pref.getInt("Six", 2500);
        int FiveDaysAgo = pref.getInt("Five", 2700);
        int FourDaysAgo = pref.getInt("Four", 2600);
        int ThreeDaysAgo = pref.getInt("Three", 2500);
        int TwoDaysAgo = pref.getInt("Two", 2890);
        int OneDayAgo = pref.getInt("One", 3100);
        int currDay = pref.getInt("TotalAmountWaterDrank", 0);

        GraphView graph = (GraphView) root.findViewById(R.id.graph);
        LineGraphSeries<DataPoint> series = new LineGraphSeries<DataPoint>(new DataPoint[] {
                new DataPoint(0, currDay),
                new DataPoint(1, OneDayAgo),
                new DataPoint(2, TwoDaysAgo),
                new DataPoint(3, ThreeDaysAgo),
                new DataPoint(4, FourDaysAgo),
                new DataPoint(5, FiveDaysAgo),
                new DataPoint(6, SixDaysAgo),
                new DataPoint(7, SevenDaysAgo),
        });
        graph.addSeries(series);
        GridLabelRenderer gridLabel = graph.getGridLabelRenderer();
        gridLabel.setHorizontalAxisTitle("Days Ago");
        gridLabel.setVerticalAxisTitle("Water drank (in mL)");
        return root;
    }

    @Override
    public void onDestroyView() {
        super.onDestroyView();
        binding = null;
    }

    public void shiftData() {
        SharedPreferences pref = getActivity().getPreferences(Context.MODE_PRIVATE);
        SharedPreferences.Editor editor = pref.edit();

        // read data
        int SixDaysAgo = pref.getInt("Six", 0);
        int FiveDaysAgo = pref.getInt("Five", 0);
        int FourDaysAgo = pref.getInt("Four", 0);
        int ThreeDaysAgo = pref.getInt("Three", 0);
        int TwoDaysAgo = pref.getInt("Two", 0);
        int OneDayAgo = pref.getInt("One", 0);
        int currDay = pref.getInt("TotalAmountWaterDrank", 0);

        // shift each data point down one day
        editor.putInt("Seven", SixDaysAgo);
        editor.putInt("Six", FiveDaysAgo);
        editor.putInt("Five", FourDaysAgo);
        editor.putInt("Four", ThreeDaysAgo);
        editor.putInt("Three", TwoDaysAgo);
        editor.putInt("Two", OneDayAgo);
        editor.putInt("One", currDay);
        editor.putInt("currDay", 0);
        editor.putInt("TotalAmountWaterDrank", 0);
        editor.apply();
    }
}