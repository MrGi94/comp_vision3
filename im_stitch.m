function full_trans = im_stitch(image1, target_image2, match_para)

  %INPUT: image1 and target_image2 are marge each other to consider the
  %matchimg parameter match_para
  %image1 is projective transform and target_image2 is affine transform
  %After both transformation average the value of transformations and make
  %the output image
  
    ima1=imread(image1);
    ima2=imread(target_image2);  
        
    T= maketform('projective',match_para');
    T2=maketform('affine',eye(3));
    
    [B, xdata, ydata] = imtransform(ima1,T);
    
    min_value=0.0;
    val_minx=min(1,xdata(1));
    val_max_imcol=max(size(ima2,2), xdata(2));
    val_miny=min(1,ydata(1));
    val_max_imrow=max(size(ima2,1), ydata(2));    

    xinfo=[val_minx  val_max_imcol];
    yinfo=[val_miny  val_max_imrow];
    trans1 = imtransform(ima1,T,'XData',xinfo,'YData',yinfo);
    trans2 = imtransform(ima2,T2,'XData',xinfo,'YData',yinfo);
    
    full_trans = plus(trans1,trans2);
    avg = plus((trans1*0.5),(trans2*0.5));    
    double = ((trans1 > min_value) & (trans2 > min_value));       
    full_trans(double) = avg(double);
end