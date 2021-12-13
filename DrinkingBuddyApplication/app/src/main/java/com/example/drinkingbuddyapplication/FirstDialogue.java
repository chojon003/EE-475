package com.example.drinkingbuddyapplication;

        import android.app.AlertDialog;
        import android.app.Dialog;
        import android.content.Context;
        import android.content.DialogInterface;
        import android.os.Bundle;

        import android.view.LayoutInflater;
        import android.view.View;
        import android.widget.EditText;

        import androidx.appcompat.app.AppCompatDialogFragment;


public class FirstDialogue extends AppCompatDialogFragment {

    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());

        LayoutInflater inflater = getActivity().getLayoutInflater();
        View view = inflater.inflate(R.layout.layout_dialog, null);

        builder.setView(view)
                .setTitle("First Time Setup")
                .setIcon(R.drawable.ic_launcher_foreground)
                .setMessage("Make sure water bottle only contains water, and is attached securely.")
                .setPositiveButton("Complete", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                        ((MainActivity) getActivity()).onSend();
                    }
                });


        return builder.create();
    }
}